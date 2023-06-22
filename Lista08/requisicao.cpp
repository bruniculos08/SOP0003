#include <bits/stdc++.h>

using namespace std;

struct solicitacao{
    unsigned int bloco_inicial, num_blocos;
    char op;
    bool fundido;
};

bool compareBloco(solicitacao s1, solicitacao s2){
    if(s1.bloco_inicial != s2.bloco_inicial) return s1.bloco_inicial < s2.bloco_inicial;
    else return s1.num_blocos < s2.num_blocos;
}

void fundirSolicitacoes(vector<solicitacao> &fila){
    vector<solicitacao> filaFusao;
    solicitacao fusao;
    bool add = false;

    for(int i = 0; i < (int) fila.size(); i++){

        if(fila[i].fundido == true) continue;

        fusao.bloco_inicial = fila[i].bloco_inicial; 
        fusao.num_blocos = fila[i].num_blocos;
        fusao.op = fila[i].op;
        fusao.fundido = false;

        for(int j = i+1; (j < (int) fila.size()) and (fusao.bloco_inicial + fusao.num_blocos >= fila[j].bloco_inicial - 1); j++){

            if(fila[i].op == 'r' and fila[j].op == 'r'){
                int end_f = fusao.bloco_inicial + fusao.num_blocos - 1;
                int end_j = fila[j].bloco_inicial + fila[j].num_blocos - 1;
                
                
                if(max(end_j, end_f) - fusao.bloco_inicial + 1 <= 64){
                    fusao.num_blocos = max(end_j, end_f) - fusao.bloco_inicial + 1;
                    fila[j].fundido = true;
                    add = true;
                }
            }

            if(fila[i].op == 'w' and fila[j].op == 'w' and fusao.bloco_inicial + fusao.num_blocos - 1 == fila[j].bloco_inicial - 1){                  
                if(fusao.num_blocos + fila[j].num_blocos <= 64){
                    fusao.num_blocos = fila[j].num_blocos + fusao.num_blocos;
                    fila[j].fundido = true;
                    add = true;
                }
            }


        }
        
        if(add == true){
            filaFusao.push_back(fusao);
            // cout << "adding to fila" << endl;
        } 
        else if(fila[i].fundido == false){
            filaFusao.push_back(fila[i]);    
            // cout << "adding to fila" << endl;
        } 
        add = false;
    }

    fila = filaFusao;
}

int main(void){
    // char fileName[] = "requisicao.txt";
    // FILE *fd;
    // fd = fopen(fileName, "r");
    // size_t read, len;
    // char * line;

    // while((read = getline(&line, &len, fd)) != -1){
    // }

    vector<solicitacao> fila;
    do{
        solicitacao x;
        cin >> x.bloco_inicial >> x.num_blocos >> x.op;
        if(x.op == 'f') break;
        x.fundido = false;

        fila.push_back(x);
        sort(fila.begin(), fila.end(), compareBloco);

        fundirSolicitacoes(fila);
        // cout << "size = " << fila.size() << endl;
    
    }while(true);

    for(solicitacao &x : fila){
        cout << x.bloco_inicial << " " << x.num_blocos << " " << x.op << endl;
    }
}