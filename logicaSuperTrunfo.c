
   //
//  superTrunfo.cpp
//  Created by Vini Cassol on 03/09/20.
//  Copyright © 2020 Vini Cassol. All rights reserved.
//  

#include <iostream>
#include <vector>
#include <fstream> // trabalhar com arquivos

using namespace std;

struct Carta
{
    string id; // no futuro serah string
    string nome;
    int    velocidadeMaxima;
    int    cilindradas;
    double zeroCem;
    int    potencia;
    double comprimento;
    int    peso;
};

struct Jogador
{
    string nome;
    vector<Carta> mao;
};

vector <Carta> baralho; // definiçao do vetor que vai armazenar todas as cartas
vector <Jogador> jogadores; //vetor para controlar cada jogador

void ImprimeBaralho()
{
    for(int i = 0; i < baralho.size(); i++)
    {
        cout << baralho[i].id << " - " << baralho[i].nome << " - " << baralho[i].velocidadeMaxima << " - " << baralho[i].cilindradas << " - " << baralho[i].zeroCem<< " - " << baralho[i].potencia<< " - " << baralho[i].comprimento<< " - " << baralho[i].peso <<       endl;
    }
}

string ajustaEspaco(string palavra)
{
    for(int i=0; i < palavra.size(); i++)
    {
        if(palavra[i] == '_')
            palavra[i] = ' ';
    }
    return palavra;
}

void LoadCartas()
{
    ifstream arquivo;
    
    arquivo.open("/Users/vini/Documents/C++/prog1/prog1/cartas.txt");
    
    if(arquivo.is_open())
    {
        cout << "Arquivo aberto para leitura\n";
        while(!arquivo.eof()) // enquanto nao for o final do arquivo
        {
            Carta temp;
            
            arquivo >> temp.id;
            arquivo >> temp.nome;
            arquivo >> temp.velocidadeMaxima;
            arquivo >> temp.cilindradas;
            arquivo >> temp.zeroCem;
            arquivo >> temp.potencia;
            arquivo >> temp.comprimento;
            arquivo >> temp.peso;
            
            temp.nome = ajustaEspaco(temp.nome); // troca '_' por ' '
            
            baralho.push_back(temp);
            
            //cout << temp.id << endl;
        }
        arquivo.close();
        
    }
    else
        cout << "Erro ao abrir arquivo\n";
    
    cout << baralho.size() << " cartas carregadas!\n";
}

void Embaralhar()
{
    
    //random_shuffle(baralho.begin(), baralho.end());
    //Trocar as cartas de posição de forma aletoria no mesmo vetor
    
    for(int i=0; i < baralho.size();  i++)
    {
        int pos = rand() % baralho.size();
        
        Carta temp = baralho[i];
        baralho[i] = baralho[pos];
        baralho[pos] = temp;
    }
    
    //Trocar as cartas de posição de forma aletoria usando um vector temporario
   /* vector<Carta> temporario;
    
    while (baralho.size()>0) {
        
        int pos = rand() % baralho.size();
        temporario.push_back(baralho[pos]); // copia para o vector temporario
        baralho.erase(baralho.begin()+pos); // apaga o elemento copiado
    }
    
    baralho = temporario;*/
}

void Distribuir()
{
    
    int j = 0; //jogador atual
    
    for(int i=0; i < baralho.size(); i++) // percorrer o baralho e dividir as cartas
    {
        jogadores[j].mao.push_back(baralho[i]);
        j++;
        
        if(j == jogadores.size())
            j = 0;
    }
    
}

void MostraStatus()
{
    for(int i = 0; i < jogadores.size(); i++ )
        cout << "Num Cartas Jogador " << i <<": " << jogadores[i].mao.size() << endl;
}

void ImprimeCartaPlayer(int v)
{
    cout << "SUA CARTA: " << jogadores[v].mao[0].id << " - " << jogadores[v].mao[0].nome << endl;
    cout << "Atributos: \n";
    cout << "1. Vel Maxima: " <<jogadores[v].mao[0].velocidadeMaxima << endl;
    cout << "2. Cilindradas: " <<jogadores[v].mao[0].cilindradas << endl;
    cout << "3. Zero a 100: " <<jogadores[v].mao[0].zeroCem << endl;
    cout << "4. Potencia: " <<jogadores[v].mao[0].potencia << endl;
    cout << "5. Comprimento: " <<jogadores[v].mao[0].comprimento << endl;
    cout << "6. Peso: " <<jogadores[v].mao[0].peso << endl;
    
}

void Jogada(int vez)
{
    
    
    int atr;
    cout << "Jogador " << vez << ", informe o numero do atributo escolhido: ";
    cin >> atr;
    
    int maiorVel = 0;
    int jVencedor = vez;
    
    switch (atr)
    {
          
        case 1:
            cout << "Atributo escolhido: VELOCIDADE\n";
            maiorVel = jogadores[vez].mao[0].velocidadeMaxima;
            
            for(int i= 0; i < jogadores.size(); i++)
            {
                cout << "Carta Jogador " << i <<": " << jogadores[i].mao[0].id << " - Vel: " << jogadores[i].mao[0].velocidadeMaxima << endl;
                
                if(i != vez ) //não compara consigo mesmo
                {
                    if(jogadores[i].mao[0].velocidadeMaxima > maiorVel)
                    {
                        maiorVel = jogadores[i].mao[0].velocidadeMaxima;
                        jVencedor = i;
                    }
                }
            }
            cout << "Vencedor: Jogador " << jVencedor << endl;
            
            for (int i= 0; i < jogadores.size(); i++ )
            {
                if(jogadores[i].mao.size() > 0)
                {
                    jogadores[jVencedor].mao.push_back( jogadores[i].mao[0]);
                    jogadores[i].mao.erase(jogadores[i].mao.begin()) ; // apaga a posicao zero
                }
            }
                
            break;
            
        case 2:
            cout << "Atributo escolhido: CILINDRADAS";
            break;
        case 3:
            cout << "Atributo escolhido: ZERO A 100";
            break;
        case 4:
            cout << "Atributo escolhido: POTENCIA";
            break;
        case 5:
            cout << "Atributo escolhido: COMPRIMENTO";
            break;
        case 6:
            cout << "Atributo escolhido: PESO";
            break;
    }
    
}

void ImprimeMaos()
{
    for(int i=0; i<jogadores.size(); i++)
    {
        cout << "======= CARTAS DO JOGADOR "<< i << "=========\n";
        for(int j=0; j<jogadores[i].mao.size(); j++)
        {
            cout << jogadores[i].mao[j].id << " - " << jogadores[i].mao[j].nome << " - " << jogadores[i].mao[j].velocidadeMaxima << " - " << jogadores[i].mao[j].cilindradas << " - " << jogadores[i].mao[j].zeroCem<< " - " << jogadores[i].mao[j].potencia<< " - " << jogadores[i].mao[j].comprimento<< " - " << jogadores[i].mao[j].peso <<       endl;
        }
    }
}

void GamePlay(int numJogadores)
{
    // O player da vez sempre visualiza a sua primeira carta
    // O player da vez escolhe o atributo para comparar
    // Os valores sao comparados
    // O jogador com maior valor do atributo leva as cartas dos coleguinhas
    // As cartas que foram embora são "removidas" da mão do coleguinha e adicionadas na mão do player da vez
    
    //TODO:
    // Empate: Nova pergunta com as mesmas cartas
    // Jogadores com zero cartas devem ser eliminados
    // O jogo acaba quando um dos jogadores estiver com todas as cartas
    
    
    bool isRunning = true;
    int  vez = 0;
    while(isRunning)
    {
        ImprimeCartaPlayer(vez);
        Jogada(vez);
        MostraStatus();
        ImprimeMaos();
        vez++;
        if(vez == jogadores.size())
        {
            vez = 0;
        }
        
        /// isRunning = false;
    }
    
    //fimDeJogo
    
}

int main()
{
    srand(time(0)); // numeros pseudo-aleatorios
    
    //TODO: Menu
    //
    // perguntar numeros de jogadores... humanos ou bots?
    // Salvar o nome dos jogadores, criar nomes para bots (atualizar struct jogador)
    // implementar jogabilidade completa
    // ranking -> jogador e numero de jogadas.... o joggador que vence mais rapido
    
    int numJogadores = 8;
    jogadores.resize(numJogadores); // Definir o numero de jogadores;
    
    LoadCartas();
    Embaralhar();
    Distribuir();
    

    
    GamePlay(numJogadores);
    
    
   // ImprimeBaralho();
   
    
}
