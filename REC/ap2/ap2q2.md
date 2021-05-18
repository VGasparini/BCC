# AP2-Q2: Roteamento Estático

## Roteador_r3:
* rot_r3_r2: 100.2.0.1/30
* rot_r3_r5: 135.0.0.1/30
* rot_r3_r6: 136.0.0.1/30
* rot_r3_r7: 137.0.0.1/30
* rot_r3_int: 100.3.3.254/22

## Rede_lan6: 100.3.0.0/22
* lan6_faixa_dhcp: 100.3.0.2 - 100.3.3.253
* lan6_dhcp: 100.3.0.1
    * lan6_dhcp_faixa: lan6_faixa_dhcp
    * lan6_dhcp_mask: 255.255.252.0
    * lan6_dhcp_dg: rot_r3_int
* dg: rot_r3_int

## Roteador_r6:
* rot_r6_int: 136.0.0.2/30
* rot_r6_ext: 168.0.0.1/30
* dg: rot_r3_r6

## Roteador_r8:
* rot_r8_int: 100.8.7.254/21
* rot_r8_ext: 168.0.0.2/30
* dg: rot_r3_ext

## Rede_lan3: 100.8.0.0/21
* lan3_faixa_dhcp: 100.8.0.2 - 100.8.7.253
* lan3_dhcp: 100.8.0.1
    * lan3_dhcp_faixa: lan3_faixa_dhcp
    * lan3_dhcp_mask: 255.255.248.0
    * lan3_dhcp_dg: rot_r8_int
* dg: rot_r8_int

## Roteador_r5:
* rot_r5_int_r3: 135.0.0.2/30
* rot_r5_int_r7: 157.0.0.1/30
* rot_r5_ext: 154.0.0.1/30
* dg: rot_r3_r5

## Roteador_r4:
* rot_R4_ext: 154.0.0.2/30
* rot_R4_int: 100.2.0254/24
* dg: rot_r5_ext

## Rede_lan2: 100.2.00/24
* lan2_faixa_dhcp: 100.2.0.2 - 100.2.0.253
* lan2_dhcp: 100.2.0.1
    * lan2_dhcp_faixa: lan2_faixa_dhcp
    * lan2_dhcp_mask: 255.255.255.0
    * lan2_dhcp_dg: rot_R4_int
* dg: rot_R4_int

## Roteador_r2:
* rot_r2_ext: 121.0.0.1/30
* rot_r2_int: 100.2.0.2/30
* dg: rot_r3_r2

## Roteador_R1:
* rot_R1_ext: 121.0.0.2/30
* rot_R1_int: 100.1.0.62/26
* dg: rot_r2_ext

## Rede_lan1: 100.1.0.0/26
* lan1_faixa_dhcp: 100.1.0.2 - 100.1.0.61
* lan1_dhcp: 100.1.0.1
    * lan1_dhcp_faixa: lan1_faixa_dhcp
    * lan1_dhcp_mask: 255.255.255.192
    * lan1_dhcp_dg: rot_R1_int
* dg: rot_R1_int

## Roteador_r7:
* rot_r7_int_r3: 137.0.0.2/30
* rot_r7_int_r5: 157.0.0.2/30
* rot_r7_ext: 179.0.0.1/30
* dg: rot_r3_r7

## Roteador_r9:
* rot_r9_int: 100.9.1.254/23
* rot_r9_ext: 179.0.0.2/30
* rot_r9_ext_r10: 191.0.0.1/30
* dg: rot_r7_ext

## Rede_lan4: 100.9.0.0/23
* lan4_faixa_dhcp: 100.9.0.2 - 100.9.0.253
* lan4_dhcp: 100.9.0.1
    * lan4_dhcp_faixa: lan4_faixa_dhcp
    * lan4_dhcp_mask: 255.255.254.255
    * lan4_dhcp_dg: rot_r9_int
* dg: rot_r9_int

## Roteador_r10:
* rot_r10_ext: 191.0.0.2/30
* rot_r10_int: 100.10.0.126/25
* dg: rot_r9_ext

## Rede_lan5: 100.10.0.0/25
* lan5_faixa_adm: 100.10.0.1 - 100.10.0.9
* lan5_faixa_dhcp: 100.10.0.10 - 100.10.0.125
* lan5_dhcp: 100.10.0.1
    * lan5_dhcp_faixa: lan5_faixa_dhcp
    * lan5_dhcp_mask: 255.255.255.127
    * lan5_dhcp_dg: rot_r10_int
* dg: rot_r10_int

## Redes
* Rede_r9_r10: 191.0.0.0/30
* Rede_r7_r9: 179.0.0.0/30
* Rede_r3_r7: 137.0.0.0/30
* Rede_r5_r7: 157.0.0.0/30
* Rede_r5_r4: 154.0.0.0/30
* Rede_r3_r5: 135.0.0.0/30
* Rede_r6_r8: 168.0.0.0/30
* Rede_r3_r6: 136.0.0.0/30
* Rede_r2_r1: 121.0.0.0/30
* Rede_r3_r2: 100.2.0.0/30

## Protocolos
* HTTP: 80/TCP
* HTTPS: 443/TCP
* SMTP: 25/TCP e 587/TCP
* FTP: 20 e 21/TCP
* DNS: 53/TCP e 53/UDP


### Roteador_r1
| Endereço Destino         | Salto     |
| ------------------------ | --------- |
| 0.0.0.0/0                | rot_r2_ext|

### Roteador_r2
| Endereço Destino         | Salto     |
| ------------------------ | --------- |
| Rede_lan1 (100.1.0.0/26) | rot_R1_ext|
| 0.0.0.0/0                | rot_r3_r2 |

### Roteador_r3
| Endereço Destino         | Salto     |
| ------------------------ | --------- |
| Rede_lan1 - 100.1.0.0/26 | rot_r3_r2 |
| Rede_lan2 - 100.2.0.0/24 | rot_r3_r5 |
| Rede_lan3 - 100.2.0.0/21 | rot_r3_r6 |
| Rede_lan4 - 100.9.0.0/23 | rot_r3_r7 |
| Rede_lan5 - 100.10.0.0/25| rot_r3_r7 |

### Roteador_r4
| Endereço Destino   | Salto      |
| ------------------ | ---------- |
| 0.0.0.0/0          | rot_r5_ext |

### Roteador_r5
| Endereço Destino         | Salto        |
| ------------------------ | ------------ |
| Rede_lan2 - 100.2.0.0/24 | rot_r4_ext   |
| Rede_lan4 - 100.9.0.0/23 | rot_r7_int_r5|
| Rede_lan5 - 100.10.0.0/25| rot_r7_int_r5|
| 0.0.0.0/0                | rot_r3_r5    |

### Roteador_r6
| Endereço Destino         | Salto     |
| ------------------------ | --------- |
| Rede_lan3 - 100.2.0.0/21 | rot_r8_ext|
| 0.0.0.0/0                | rot_r3_r6 |

### Roteador_r7
| Endereço Destino         | Salto        |
| ------------------------ | ------------ |
| Rede_lan4 - 100.9.0.0/23 | rot_r9_ext   |
| Rede_lan5 - 100.10.0.0/25| rot_r9_ext   |
| Rede_lan2 - 100.2.00/24  | rot_r5_int_r7|
| 0.0.0.0/0                | rot_r3_r7    |

### Roteador_r8
| Endereço Destino         | Salto     |
| ------------------------ | --------- |
| 0.0.0.0/0                | rot_r3_ext|

### Roteador_r9
| Endereço Destino         | Salto      |
| ------------------------ | ---------- |
| Rede_lan5 - 100.10.0.0/25| rot_r10_ext|
| 0.0.0.0/0                | rot_r7_ext |

