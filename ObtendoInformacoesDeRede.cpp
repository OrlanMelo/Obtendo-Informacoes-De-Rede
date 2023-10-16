#include <Windows.h>
#include <iphlpapi.h>
#include <string>
#include <iostream>
#include <fstream>
#pragma comment(lib,"kernel32.lib")
#pragma comment(lib,"iphlpapi.lib")

using namespace std;

class cFuncoes
{
private:

	PIP_ADAPTER_INFO Adaptador;
	PIP_ADAPTER_INFO Resultado;

public:

	void ObterInformacoesDeRede()
	{
		ULONG Bytes = sizeof(IP_ADAPTER_INFO);

		Adaptador = (IP_ADAPTER_INFO*)malloc(sizeof(IP_ADAPTER_INFO));

		if(GetAdaptersInfo(Adaptador, &Bytes));
		free(Adaptador);

		Adaptador = (IP_ADAPTER_INFO*)malloc(Bytes);

		if (GetAdaptersInfo(Adaptador, &Bytes) == NO_ERROR)
		{
			Resultado = Adaptador;

			for (int i = 0; i < Resultado->AddressLength; i++)
			{
				cout << "GUID: " << Resultado[i].AdapterName << '\n';
				cout << "Endereço: " << Resultado[i].IpAddressList.IpAddress.String << '\n';
				cout << "Index: " << Resultado[i].Index << '\n';

				switch (Resultado[i].Type)
				{
				case MIB_IF_TYPE_ETHERNET:
					cout << "Tipo: Ethernet" << '\n';
					break;
				case MIB_IF_TYPE_PPP:
					cout << "Tipo: PPP" << '\n';
					break;
				case MIB_IF_TYPE_LOOPBACK:
					cout << "Tipo: Loopback" << '\n';
					break;
				case MIB_IF_TYPE_SLIP:
					cout << "Tipo: ATM" << '\n';
					break;
				case IF_TYPE_IEEE80211:
					cout << "Tipo: Sem fio" << '\n';
					break;
				default:
					break;
				}

				if (Resultado[i].DhcpEnabled)
				{
					cout << "Servidor DHCP: " << Resultado[i].DhcpServer.IpAddress.String << '\n';
				}
				else
				{
					cout << "Servidor DHCP: Desativado" << '\n';
				}

				cout << "Dispositivo: " << Resultado[i].Description << '\n' << '\n';
			}

			if(Adaptador)
				free(Adaptador);
		}
		else
		{
			cout << "Ocorreu um erro ao obter informações, veja o código de erro: " << GetLastError();
		}
	}

}Funcoes;

int main()
{
	cout << "O assistente está verificando propriedades de adaptador de rede...";

	Funcoes.ObterInformacoesDeRede();

	system("pause");
}
