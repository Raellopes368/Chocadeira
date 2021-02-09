# Chocadeira com Arduino e Sensor de Temperatura DHT11

## Descrição

Esse código é responsável por fazer o controle de uma lâmpada para controlar a temperatura de dentro de uma caixa pequena de isopor.

## Instalação

Faça o clone do projeto com o git via https:   
```git clone https://github.com/Raellopes368/Chocadeira.git```  


Ou com ssh:  

```git clone git@github.com:Raellopes368/Chocadeira.git```  


Ou faça o download do código zipado via github.  

## Dependêncas

As dependências do projeto são a lib **DHT.h** que você pode [baixar aqui](https://github.com/adafruit/DHT-sensor-library) e também a lib [LiquidCrystal_I2C.h](https://github.com/fdebrabander/Arduino-LiquidCrystal-I2C-library)

## Configurações iniciais

Descomente as linhas 77 à 82 na primeira vez que carregar o código, isso irá gravar na memória EEPRON, após carregar, comente novamente essas linhas e volte a carregar o código no seu arduino.
