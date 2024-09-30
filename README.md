# arc2023

## requirements

* raspi
  * model: Raspberry Pi Model B+
  * OS : Raspberry Pi OS
* Arduino
  * 不明

## raspi settings

OS側で必要となる作業は以下の通りです。

### user add

root ユーザで以下を実行します。

```
useradd arc -m -G sudo
passwd arc
```

## download ARC2023

arc ユーザで以下を実行します。

```
git clone https://github.com/acchi17/ARC2023.git ARC2023
cd ARC2023
chmod 700 SetupAutoStart.sh
sudo bash SetupAutoStart.sh
```

### setting IP address

eth0 に `192.168.5.11/24` を割り当てます。設定方法は何でもいいです。
