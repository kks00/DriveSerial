# DriveSerial
-------------
## PC에 장착되어 있는 디스크 드라이브 장치의 고유 번호를 가져오는 프로그램입니다.
-------------

### 원리
```
wmic path Win32_LogicalDiskToPartition
```
antecedent, dependent 컬럼의 데이터를 통해 디스크 드라이브의 DeviceID, Logical Drive 문자를 가져옵니다.
![다운로드](https://media.discordapp.net/attachments/1025908716316393484/1190960697618747422/0.png?ex=65a3b395&is=65913e95&hm=c5d4284b73468fa1755a1358faac2fa1fca33e384c822843edea802d606e06f9&=&format=webp&quality=lossless&width=918&height=501)

-------------

```
wmic diskdrive get index, serialnumber
```
드라이브의 DeviceID, SerialNumber 정보를 가져옵니다.
![다운로드](https://media.discordapp.net/attachments/1025908716316393484/1191182902331969546/1.png?ex=65a48287&is=65920d87&hm=a9090cc687805e12fcfba382adfd3360a4d519c704144e33838842cdc8425c48&=&format=webp&quality=lossless&width=916&height=516)


-------------

![다운로드](https://media.discordapp.net/attachments/1025908716316393484/1190961264986439730/2.png?ex=65a3b41c&is=65913f1c&hm=32c015ab7688457383a17e507805637b7465cc80acf02aa1e9edeb46b79e2f66&=&format=webp&quality=lossless&width=918&height=480)
