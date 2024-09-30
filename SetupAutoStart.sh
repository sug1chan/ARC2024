#!/bin/bash

systemctl stop arc2023
cp arc2023.service /etc/systemd/system/
ln -sf /home/arc/ARC2023/arc2023.service /etc/systemd/system/
systemctl daemon-reload
systemctl enable arc2023.service
systemctl start arc2023.service
