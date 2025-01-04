# Laboratório de Física Aplicada à Computação - IPBeja (ESTIG)

Este repositório contém o código desenvolvido para o laboratório de **Física Aplicada à Computação** do curso de **Engenharia Informática** no **Instituto Politécnico de Beja (ESTIG)**.

## Descrição do Projeto

O objetivo deste laboratório é coletar, processar e visualizar dados de sensores conectados a um Arduino Nano 33 BLE Sense Rev2. Os dados incluem medições de temperatura, humidade, pressão, aceleração, giroscópio e magnetômetro. O projeto envolve a comunicação serial entre o Arduino e o computador, além da análise dos dados utilizando o Jupyter do Anaconda.

## Estrutura do Projeto

- `LAB.py`: Script principal para coletar e processar os dados dos sensores.
- `sensor_data.csv`: Arquivo CSV contendo os dados coletados durante a execução do script.

## Requisitos

- Python 3.12.7
- Bibliotecas Python: `serial`, `time`, `numpy`, `pandas`, `matplotlib`, `seaborn`, `prettytable`
