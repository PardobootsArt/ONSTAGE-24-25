# Importa as bibliotecas que serão utilizadas no programa
# sounddevice: para capturar áudio do microfone
# queue: para organizar os pedaços de áudio enquanto são processados
# json: para interpretar o texto que vem do reconhecimento de fala
# vosk: biblioteca que transforma fala em texto
# serial: para enviar comandos para o Arduino via cabo USB
# time: para adicionar pausas se necessário
import sounddevice as sd
import queue
import json
from vosk import Model, KaldiRecognizer
import serial
import serial.tools.list_ports

# Função que tenta encontrar automaticamente qual porta USB o Arduino está usando
def encontrar_arduino():
    portas = serial.tools.list_ports.comports()  # Lista todas as portas disponíveis
    for porta in portas:
        # Verifica se a porta tem características de um Arduino
        if "Arduino" in porta.description or "CH340" in porta.description:
            return porta.device  # Se encontrar, retorna o nome da porta (ex: COM3)
    return None  # Se não encontrar, retorna None (nada)


# Tenta se conectar automaticamente ao Arduino
porta_arduino = encontrar_arduino()
if porta_arduino:
    # Se encontrou, cria a conexão com o Arduino usando a porta encontrada e velocidade 9600
    arduino = serial.Serial(porta_arduino, 9600)
    print(f"Arduino conectado na porta: {porta_arduino}")
else:
    # Se não encontrou automaticamente, pede para o usuário digitar manualmente a porta COM
    porta_manual = input("Arduino não encontrado automaticamente. Informe a porta COM (ex: COM3): ")
    arduino = serial.Serial(porta_manual, 9600)
    print(f"Arduino conectado manualmente na porta: {porta_manual}")


# Define as palavras que o programa vai entender e os números que serão enviados ao Arduino
comandos = {
    "morning": "1",     # Se reconhecer a palavra "dia", envia "1"
    "evening": "2",   # Se reconhecer a palavra "noite", envia "2"
    "final": "3"      # Se reconhecer a palavra "fim", envia "3"
}


# Esse modelo é responsável por entender o áudio falado
model = Model("C:/Users/Pardoboots/PycharmProjects/Onstage_Regional_2025/models/vosk-model-small-en-us-0.15")

# Cria um reconhecedor de fala com o modelo e define que o áudio será processado a 16000 Hz
rec = KaldiRecognizer(model, 16000)

# Cria uma fila para armazenar os pedaços de áudio que serão processados
q = queue.Queue()


# Esta função é chamada automaticamente toda vez que o microfone capta um novo pedaço de áudio
def callback(indata, frames, time_info, status):
    if status:
        print(status)  # Se houver algum problema com o áudio, será mostrado aqui
    q.put(bytes(indata))  # Coloca o pedaço de áudio na fila para ser reconhecido


# Inicia a escuta do microfone
with sd.RawInputStream(samplerate=16000, blocksize=8000, dtype='int16',
                       channels=1, callback=callback):
    print(">>> Pronto para escutar. Diga 'morning', 'evening' ou 'final'...")

    # Loop que roda continuamente, ouvindo e reconhecendo a fala
    while True:
        data = q.get()  # Pega o próximo pedaço de áudio da fila

        # Verifica se o áudio atual pode ser reconhecido como uma palavra
        if rec.AcceptWaveform(data):
            resultado = rec.Result()  # Resultado do reconhecimento (em formato texto + JSON)
            texto = json.loads(resultado).get("text", "").lower()  # Pega o texto reconhecido e transforma em minúsculo
            print(f"Reconhecido: {texto}")  # Mostra no console o que foi entendido

            # Verifica se alguma das palavras definidas está no que foi reconhecido
            for palavra in comandos:
                if palavra in texto:
                    comando = comandos[palavra]  # Pega o número correspondente à palavra
                    print(f"Enviando para Arduino o comando: '{comando}' referente à palavra '{palavra}'")

                    try:
                        arduino.write(comando.encode())  # Envia o número como texto para o Arduino via USB
                        print(f"Comando '{comando}' enviado para o Arduino.")
                    except Exception as e:
                        # Mostra um erro caso algo dê errado no envio
                        print(f"Erro ao enviar para o Arduino: {e}")
                    break  # Sai do loop de palavras para evitar múltiplos envios ao mesmo tempo
