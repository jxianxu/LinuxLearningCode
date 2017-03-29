#/bin/bash
uptime | sed -n '/,/s/,/ /gp' |
gawk '{if($4 == "days" || $4 == "day") {print $2,$3,$4,$5} else {print $2,$3}}'
