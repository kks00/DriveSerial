#define _CRT_SECURE_NO_WARNINGS
#define _SILENCE_STDEXT_HASH_DEPRECATION_WARNINGS

#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>

#include <string>
#include <vector>
#include <hash_map>
#include <sstream>
#include <iostream>
using namespace std;

vector<string> split(string line, char delim) {
	vector<string> result;
	result.clear();

	stringstream ss(line);
	string curr_token;
	while (getline(ss, curr_token, delim)) {
		if (curr_token.length() > 0)
			result.push_back(curr_token);
	}
	return result;
}

string split(string line, string left, string right) {
	size_t left_cursor = line.find(left, 0);
	if (left_cursor == string::npos)
		return "";
	left_cursor += left.length();

	size_t right_cursor = line.find(right, left_cursor);
	if (right_cursor == string::npos)
		return "";

	return line.substr(left_cursor, right_cursor - left_cursor);
}

typedef struct logical_drive {
	string device_id, serial_number;
};
hash_map<string, logical_drive> logical_drives;

int main() {
	stringstream lgdrive_stream("");
	lgdrive_stream.clear();
	FILE *wmic_stream = _popen("WMIC Path Win32_LogicalDiskToPartition", "r");
	if (wmic_stream) {
		char buf[1024];
		memset(buf, 0, 1024);
		while (fread(buf, sizeof(char), 1024, wmic_stream) > 0) {
			lgdrive_stream << buf;
		}
		fclose(wmic_stream);
	}

	string curr_line;
	while (getline(lgdrive_stream, curr_line)) {
		logical_drive curr_lgdrive;
		curr_lgdrive.serial_number = "";

		string device_id = split(curr_line, "DeviceID=\"Disk #", ", ");
		if (device_id.length() < 1)
			continue;
		curr_lgdrive.device_id = device_id;

		string logical_id = split(curr_line, "LogicalDisk.DeviceID=\"", "\"");
		if (logical_id.length() < 1)
			continue;

		logical_drives.insert(pair<string, logical_drive>(logical_id, curr_lgdrive));
	}

	stringstream phydrive_stream("");
	phydrive_stream.clear();
	wmic_stream = _popen("WMIC diskdrive get Index, SerialNumber", "r");
	if (wmic_stream) {
		char buf[1024];
		memset(buf, 0, 1024);
		while (fread(buf, sizeof(char), 1024, wmic_stream) > 0) {
			phydrive_stream << buf;
		}
		fclose(wmic_stream);
	}

	int count = 0;
	while (getline(phydrive_stream, curr_line)) {
		if (count++ > 0) {
			vector<string> tokens = split(curr_line, ' ');
			if (tokens.size() >= 2) {
				string device_id = *tokens.begin();
				string serial_number = *(tokens.begin() + 1);

				for (hash_map<string, logical_drive>::iterator iter = logical_drives.begin(); iter != logical_drives.end(); iter++)
					if (iter->second.device_id == device_id)
						iter->second.serial_number = serial_number;
			}
		}
	}

	for (hash_map<string, logical_drive>::iterator iter = logical_drives.begin(); iter != logical_drives.end(); iter++)
		printf("logical_id = %s, device_id = %s, serial_number = %s\n", iter->first.c_str(), iter->second.device_id.c_str(), iter->second.serial_number.c_str());

	system("pause");
	return 0;
}