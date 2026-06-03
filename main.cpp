#include <iostream>
#include <string>
#include <windows.h>
#include <fstream>
#include <iomanip> 
#include <ctime>   // TAREFA 2 (Commit 2)

using namespace std;

// ADIÇÃO CRIATIVA AUTORAL
void carregarEfeito(string mensagem) {
    cout << mensagem;
    for (int i = 0; i < 3; i++) {
        Sleep(300);
        cout << ".";
    }
    Sleep(200);
    cout << " [OK]" << endl;
}

// ADIÇÃO CRIATIVA AUTORAL
void desenharGrafico(float mediaFinal) {
    int blocos = mediaFinal;
    cout << "[";
    for (int i = 0; i < 10; i++) {
        if (i < blocos) {
            cout << "█";
        } else {
            cout << "░"; 
        }
    }
    cout << "] ";
}

int main()
{
    SetConsoleOutputCP(65001);
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); // ADIÇÃO CRIATIVA AUTORAL

    // Estruturas de dados e variáveis
    string nomes[20];
    int qtdAlunos = 0;
    float notas[20][5];
    float media[20];
    int qtdDisciplinas = 0;
    int opcaoInicial;

    // ADIÇÃO CRIATIVA AUTORAL
    string listaMaterias[4] = {"Português", "Matemática", "Humanas", "Ciências"};
    string disciplinasEscolhidas[5]; 
    float somaDisciplinas[5] = {0, 0, 0, 0, 0}; 
    float maiorNotaPorMateria[5] = {0, 0, 0, 0, 0}; // ADIÇÃO CRIATIVA AUTORAL: Monitora o recorde de nota de cada matéria

    do {
        // ADIÇÃO CRIATIVA AUTORAL
        cout << "\n┌────────────────────────────────────────┐" << endl;
        cout << "│        SISTEMA DE NOTAS v4.1           │" << endl;
        cout << "├────────────────────────────────────────┤" << endl;
        cout << "│  1 - Novo Relatório                    │" << endl;
        cout << "│  2 - Ver Relatório Salvo               │" << endl;
        cout << "│  3 - Sobre o Sistema                   │" << endl; // TAREFA 1 (Commit 1)
        cout << "│  4 - Gerar Relatório de Reprovados     │" << endl; // OPCIONAL C
        cout << "│  0 - Sair                              │" << endl;
        cout << "└────────────────────────────────────────┘" << endl;
        cout << "Escolha uma opção: ";
        cin >> opcaoInicial;

        // ADIÇÃO CRIATIVA AUTORAL
        if (cin.fail()) {
            cin.clear();
            cin.ignore(10000, '\n');
            opcaoInicial = -1;
        }

        switch (opcaoInicial) {
            case 1: { // CASO 1: FLUXO DE CADASTRO E NOVO RELATÓRIO
                system("cls"); // ADIÇÃO CRIATIVA AUTORAL
                do {
                    cout << "\nQuantidade de alunos (1 a 20): ";
                    cin >> qtdAlunos;
                } while (qtdAlunos < 1 || qtdAlunos > 20);

                cin.ignore();

                for (int i = 0; i < qtdAlunos; i++) {
                    // OPCIONAL A (BÔNUS)
                    do {
                        cout << "Nome do aluno " << i + 1 << ": ";
                        getline(cin, nomes[i]);
                        if(nomes[i].empty()) {
                            cout << "O nome não pode estar em branco! Tente novamente.\n";
                        }
                    } while (nomes[i].empty());
                }

                do {
                    cout << "\nQuantidade de disciplinas (1 a 4): ";
                    cin >> qtdDisciplinas;
                    if (cin.fail()) {
                        cin.clear();
                        cin.ignore(10000, '\n');
                        qtdDisciplinas = -1; 
                    }
                } while (qtdDisciplinas < 1 || qtdDisciplinas > 4);

                // ADIÇÃO CRIATIVA AUTORAL
                cout << "\n--- SELEÇÃO DE DISCIPLINAS ---" << endl;
                for (int j = 0; j < qtdDisciplinas; j++) {
                    int opcao = -1;
                    do {
                        cout << "\nEscolha a disciplina " << j + 1 << ":" << endl;
                        for (int m = 0; m < 4; m++) {
                            cout << m + 1 << ". " << listaMaterias[m] << endl;
                        }
                        cout << "Opção: ";
                        cin >> opcao;

                        if (cin.fail() || opcao < 1 || opcao > 4) {
                            cin.clear();
                            cin.ignore(10000, '\n');
                            cout << "Opção inválida!" << endl;
                            opcao = -1;
                        }
                    } while (opcao == -1);
                    
                    disciplinasEscolhidas[j] = listaMaterias[opcao - 1];
                }

                // Reinicialização das variáveis de controle estatístico
                for(int j=0; j<5; j++) {
                    somaDisciplinas[j] = 0;
                    maiorNotaPorMateria[j] = -1;
                }

                // Entrada de Notas
                for (int i = 0; i < qtdAlunos; i++) {
                    cout << "\n▶ Inserindo notas de: " << nomes[i] << endl;
                    float soma = 0;
                    for (int j = 0; j < qtdDisciplinas; j++) {
                        do {
                            cout << "  " << disciplinasEscolhidas[j] << " (0 a 10): "; 
                            cin >> notas[i][j];

                            if (cin.fail()) {
                                cin.clear();
                                cin.ignore(10000, '\n');
                                notas[i][j] = -1;
                            }
                        } while (notas[i][j] < 0 || notas[i][j] > 10);
                        soma += notas[i][j];
                        somaDisciplinas[j] += notas[i][j]; // ADIÇÃO CRIATIVA AUTORAL
                        
                        // ADIÇÃO CRIATIVA AUTORAL: Mapeia o recorde de nota obtido nesta matéria
                        if (notas[i][j] > maiorNotaPorMateria[j]) {
                            maiorNotaPorMateria[j] = notas[i][j];
                        }
                    }
                    media[i] = soma / qtdDisciplinas;
                }

                system("cls");
                cout << "\n";
                carregarEfeito("Processando médias e gerando gráficos");

                // ==================================================
                // EXIBIÇÃO DO RELATÓRIO NO CONSOLE (INOVAÇÃO VISUAL)
                // ==================================================
                cout << "\n==================================================" << endl;
                cout << "             RELATÓRIO DE DESEMPENHO              " << endl;
                cout << "==================================================" << endl;
                
                int aprovados = 0, recuperacao = 0, reprovados = 0;
                
                // OPCIONAL B (BÔNUS)
                float maiorMedia = -1, menorMedia = 11;
                string alunoMaior = "", alunoMenor = "";
                
                cout << fixed << setprecision(1); 

                for (int i = 0; i < qtdAlunos; i++) {
                    // OPCIONAL B (BÔNUS)
                    if (media[i] > maiorMedia) { maiorMedia = media[i]; alunoMaior = nomes[i]; }
                    if (media[i] < menorMedia) { menorMedia = media[i]; alunoMenor = nomes[i]; }

                    cout << "\nALUNO(A): " << nomes[i] << endl;
                    // ADIÇÃO CRIATIVA AUTORAL
                    cout << "┌──────────────────────────────┬─────────┐" << endl;
                    cout << "│ " << left << setw(28) << "Disciplina" << "│ " << setw(7) << "Nota" << "│" << endl;
                    cout << "├──────────────────────────────┼─────────┤" << endl;
                    
                    for (int j = 0; j < qtdDisciplinas; j++) {
                        cout << "│ " << left << setw(28) << disciplinasEscolhidas[j] 
                             << "│ " << setw(7) << notas[i][j] << "│" << endl;
                    }
                    cout << "└──────────────────────────────┴─────────┘" << endl;
                    
                    // ADIÇÃO CRIATIVA AUTORAL
                    cout << "RENDIMENTO: ";
                    desenharGrafico(media[i]);
                    cout << "MÉDIA: " << media[i] << " - ";

                    // ADIÇÃO CRIATIVA AUTORAL
                    if (media[i] >= 7) {
                        SetConsoleTextAttribute(hConsole, 10);
                        cout << "[APROVADO]" << endl;
                        aprovados++;
                    }
                    else if (media[i] >= 5) {
                        SetConsoleTextAttribute(hConsole, 14); 
                        cout << "[RECUPERAÇÃO]" << endl;
                        recuperacao++;
                    }
                    else {
                        SetConsoleTextAttribute(hConsole, 12);
                        cout << "[REPROVADO]" << endl;
                        reprovados++;
                    }
                    SetConsoleTextAttribute(hConsole, 7);
                    cout << "──────────────────────────────────────────────────" << endl;
                }

                // ADIÇÃO CRIATIVA AUTORAL: Descobre qual matéria teve a menor média geral da turma
                float piorMediaMateria = 11.0;
                string materiaMaisDificil = "";
                for (int j = 0; j < qtdDisciplinas; j++) {
                    float mediaMateriaAtual = somaDisciplinas[j] / qtdAlunos;
                    if (mediaMateriaAtual < piorMediaMateria) {
                        piorMediaMateria = mediaMateriaAtual;
                        materiaMaisDificil = disciplinasEscolhidas[j];
                    }
                }

                // ADIÇÃO CRIATIVA AUTORAL
                float percentualAprovados = ((float)aprovados / qtdAlunos) * 100.0;

                cout << "\n==================================================" << endl;
                cout << "               MÉTRICAS DA TURMA                  " << endl;
                cout << "==================================================" << endl;
                cout << "• Aprovados:   " << aprovados << " aluno(s)" << endl;
                cout << "• Recuperação: " << recuperacao << " aluno(s)" << endl;
                cout << "• Reprovados:  " << reprovados << " aluno(s)" << endl;
                cout << "• Taxa de Aproveitamento: " << percentualAprovados << "%" << endl;
                cout << "──────────────────────────────────────────────────" << endl;
                // OPCIONAL B (BÔNUS)
                cout << "🏆 Destaque (Maior Média): " << alunoMaior << " (" << maiorMedia << ")" << endl;
                cout << "⚠️ Atenção (Menor Média):   " << alunoMenor << " (" << menorMedia << ")" << endl;
                cout << "──────────────────────────────────────────────────" << endl;
                
                // ADIÇÃO CRIATIVA AUTORAL: Exibição dos novos dados estatísticos inteligentes
                cout << "🚨 Disciplina Mais Desafiadora: " << materiaMaisDificil << " (Média: " << piorMediaMateria << ")" << endl;
                cout << "🥇 Maior Nota Registrada por Matéria:" << endl;
                for (int j = 0; j < qtdDisciplinas; j++) {
                    cout << "   - " << disciplinasEscolhidas[j] << ": " << maiorNotaPorMateria[j] << endl;
                }
                cout << "==================================================" << endl;

                // TAREFA 2 (Commit 2)
                ofstream arquivo("relatorio.txt");
                if (arquivo.is_open()) {
                    time_t agora = time(0);
                    char* dataHora = ctime(&agora);
                    
                    arquivo << "Data do relatorio: " << dataHora; 
                    arquivo << "==================================================\n";
                    arquivo << "               RELATORIO DE NOTAS                 \n";
                    arquivo << "==================================================\n";
                    
                    for (int i = 0; i < qtdAlunos; i++) {
                        arquivo << "Aluno: " << left << setw(20) << nomes[i] 
                                << " | Media: " << setw(5) << media[i] << " | Situacao: ";
                        if (media[i] >= 7) arquivo << "Aprovado\n";
                        else if (media[i] >= 5) arquivo << "Recuperacao\n";
                        else arquivo << "Reprovado\n";
                    }
                    arquivo << "──────────────────────────────────────────────────\n";
                    arquivo << "Resumo: " << aprovados << " aprovados, " << recuperacao << " em recuperacao, " << reprovados << " reprovados.\n";
                    arquivo << "Taxa de Aproveitamento: " << percentualAprovados << "%\n";
                    // OPCIONAL B (BÔNUS)
                    arquivo << "Maior media: " << alunoMaior << " (" << maiorMedia << ")\n";
                    arquivo << "Menor media: " << alunoMenor << " (" << menorMedia << ")\n";
                    arquivo << "==================================================\n";
                    arquivo.close();
                    cout << "\n";
                    carregarEfeito("Exportando dados para relatorio.txt");
                }
                break;
            }
            case 2: { // LEITURA DO ARQUIVO SALVO
                system("cls");
                ifstream leitura("relatorio.txt");
                if (leitura.is_open()) {
                    string linha;
                    cout << "\n--- CONTEÚDO DO ARQUIVO SALVO ---\n";
                    while (getline(leitura, linha)) {
                        cout << linha << endl;
                    }
                    leitura.close();
                    cout << "──────────────────────────────────────────────────\n";
                    
                    // ADIÇÃO CRIATIVA AUTORAL: Registra data e hora de quando o arquivo foi consultado (Arquivo de Auditoria/Log)
                    ofstream logAcesso("acessos.txt", ios::app);
                    if (logAcesso.is_open()) {
                        time_t agoraLog = time(0);
                        char* dataHoraLog = ctime(&agoraLog);
                        logAcesso << "O arquivo relatorio.txt foi lido em: " << dataHoraLog;
                        logAcesso.close();
                    }
                    
                } else {
                    cout << "\n[Aviso] Nenhum relatório salvo encontrado." << endl;
                }
                break;
            }
            case 3: { // TAREFA 1 (Commit 1)
                system("cls");
                cout << "\n=== SOBRE ===" << endl;
                cout << "Sistema de Notas v4.1" << endl;
                cout << "Desenvolvido por: Ana Júlia de Lima Paiva" << endl; 
                cout << "Turma: LOPAL 2026 - SENAI-SP" << endl;
                cout << "====================" << endl;
                break;
            }
            case 4: { // OPCIONAL C (BÔNUS)
                system("cls");
                if (qtdAlunos == 0) {
                    cout << "\n[!] É necessário rodar o relatório (Opção 1) primeiro para ter dados!" << endl;
                    break;
                }
                
                ofstream arqReprovados("reprovados.txt");
                if (arqReprovados.is_open()) {
                    time_t agora = time(0);
                    char* dataHora = ctime(&agora);
                    
                    arqReprovados << "Data do relatorio: " << dataHora;
                    arqReprovados << "=== LISTA DE ALUNOS REPROVADOS ===\n\n";
                    
                    int cont = 0;
                    for (int i = 0; i < qtdAlunos; i++) {
                        if (media[i] < 5) { 
                            arqReprovados << "• " << nomes[i] << " (Média: " << media[i] << ")\n";
                            cont++;
                        }
                    }
                    if (cont == 0) arqReprovados << "Nenhum aluno reprovado nesta listagem! 🎉\n";
                    
                    arqReprovados.close();
                    carregarEfeito("Filtrando alunos com notas baixas");
                    cout << "\n[OK] 'reprovados.txt' gerado com sucesso com " << cont << " registro(s)." << endl;
                }
                break;
            }
            case 0:
                cout << "\nSaindo... Programa encerrado." << endl;
                break;
            default:
                cout << "\nOpção inválida!" << endl;
                break;
        }
    } while (opcaoInicial != 0);

    return 0;
}