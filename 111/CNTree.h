#ifndef CNTREE_H
#define CNTREE_H
#include <vector>

using namespace std;
class CNode
{
    public:
        //contiene a los n hijos
        vector <CNode *> c_hijos;//1 es blancas 2 es negras
        int nivel;
        int m_player; // 1 o 2 segun el jugador
        int **tablero_estado;


        CNode(int **matrizEstado,int n,int var_m_player)
        {
            tablero_estado = matrizEstado;
            nivel = n;
            m_player = var_m_player;
        }
        ///////////////////////////////movimientos /////////////////////////////////////////////////

        bool mover_izq(int y,int x,int **&matriz_futuro)
        {
            int new_y =  aux_calc(y,1);
            if(x-1 >= 0 && aux_calc2(new_y) && tablero_estado[new_y][x-1] == 0)
            {
                matriz_futuro[y][x] = 0;
                matriz_futuro[new_y][x-1] = m_player;
                return 1;
            }
            return 0;
        }

        bool mover_der(int y, int x,int **&matriz_futuro)
        {
            int new_y =  aux_calc(y,1);
            if(x+1 < 8 && aux_calc2(new_y) && tablero_estado[new_y][x+1] == 0)
            {
                matriz_futuro[y][x] = 0;
                matriz_futuro[new_y][x+1] = m_player;
                return 1;
            }
            return 0;
        }

        bool comer_izq(int y,int x,int **&matriz_futuro)
        {
            if(x-2 >= 0 && aux_calc2(aux_calc(y,2)) && tablero_estado[aux_calc(y,1)][x-1] !=0 && tablero_estado[aux_calc(y,1)][x-1] !=m_player )
            {
                matriz_futuro[y][x] = 0;
                matriz_futuro[aux_calc(y,1)][x-1] = 0;
                matriz_futuro[aux_calc(y,2)][x-2] = m_player;
                return 1;
            }
            return 0;
        }

        bool comer_der(int y, int x,int **&matriz_futuro)
        {
            if(x+2 < 8 && aux_calc2(aux_calc(y,2)) && tablero_estado[aux_calc(y,1)][x+1] !=0 && tablero_estado[aux_calc(y,1)][x+1] !=m_player )
            {
                matriz_futuro[y][x] = 0;
                matriz_futuro[aux_calc(y,1)][x+1] = 0;
                matriz_futuro[aux_calc(y,2)][x+2] = m_player;
                return 1;
            }
            return 0;
        }

        //aux_calc1 y aux_calc2 para que las funciones
        int aux_calc(int y,int sum_res)
        {
            if(m_player==1)
                return y+sum_res;
            return y-sum_res;
        }
        bool aux_calc2(int y)
        {
            if(m_player==1)
                return y<8;
            return y>=0;
        }
        ///////////////////////////////////////////////////////////////////////////////



        ///imprimir tablero_estado
        void imprimir_tablero()
        {
            for(int i = 0;i<8;i++)
            {
                for(int j=0;j<8;j++)
                {
                    cout << tablero_estado[i][j] << " ";
                }
                cout << "\n";
            }
            cout << endl << endl;
        }

        ~CNode()
        {
            delete[] tablero_estado;
        }


};

class CNTree
{
    public:

        int nivel_max;
        int ia_color;
        CNode *c_root;

        CNTree(int **matriz_ini, int n, int var_ia_color)
        {
            nivel_max = n;
            ia_color = var_ia_color;

            c_root = new CNode(matriz_ini,1,ia_color);
            hijos(c_root);

        }

        ///funcion recursiva para la creacion de nodos segun el nivel

        void natalidad(CNode *aux)
        {
            if(!aux->c_hijos.size() || aux->nivel == nivel_max )return;
            for(int i=0;i<aux->c_hijos.size();i++)
            {
                hijos(aux->c_hijos[i]);
                natalidad(aux->c_hijos[i]);
            }

        }

        ///crea los hijos mandando el nodo como parametro
        void hijos(CNode *aux)
        {
            //CNode *aux = c_root;
            CNode *n_aux;
            int **tablero_act_aux;
            bool comer_primero;
            for(int i = 0;i<8;i++)

                for(int j=0;j<8;j++)
                {
                    if(aux->tablero_estado[i][j] == aux->m_player)
                    {
                        comer_primero = false;
                        tablero_act_aux=copiar_matriz(aux->tablero_estado);
                        if(aux->comer_der(i,j,tablero_act_aux))
                        {
                            n_aux = new CNode(tablero_act_aux,aux->nivel+1,aux->m_player == 1?2:1);
                            aux->c_hijos.push_back(n_aux);
                            comer_primero = true;
                        }

                        tablero_act_aux=copiar_matriz(aux->tablero_estado);
                        if(aux->comer_izq(i,j,tablero_act_aux))
                        {
                            n_aux = new CNode(tablero_act_aux,aux->nivel+1,aux->m_player == 1?2:1);
                            aux->c_hijos.push_back(n_aux);
                            comer_primero = true;
                        }

                        tablero_act_aux=copiar_matriz(aux->tablero_estado);
                        if(aux->mover_der(i,j,tablero_act_aux) && !comer_primero)
                        {
                            n_aux = new CNode(tablero_act_aux,aux->nivel+1,aux->m_player == 1?2:1);
                            aux->c_hijos.push_back(n_aux);
                        }

                        tablero_act_aux=copiar_matriz(aux->tablero_estado);
                        if(aux->mover_izq(i,j,tablero_act_aux) && !comer_primero)
                        {
                            n_aux = new CNode(tablero_act_aux,aux->nivel+1,aux->m_player == 1?2:1);
                            aux->c_hijos.push_back(n_aux);

                        }
                    }
                }
        }

        ///funcion auxiliares
        void imprimirComportamiento(CNode *p)
        {
            cout << p->c_hijos.size()<< endl;
            p->imprimir_tablero();            if(!p->c_hijos.size())return;


            for(int i=0;i<p->c_hijos.size();i++)
            {
                imprimirComportamiento(p->c_hijos[i]);
            }
        }

        ///copia la matriz del nodo
        int **copiar_matriz(int **m)
        {
            int **copia;
            copia = new int *[8];
            for(int i=0;i<8;i++)
                copia[i] = new int[8];

            for(int i=0;i<8;i++)
                for(int j=0;j<8;j++)
                {
                    copia[i][j] =m[i][j];
                }
            return copia;
        }



        ///funciones min max
        int min_max(CNode *p)
        {
            int cont_p1 = 0;
            int cont_p2 = 0;

            for(int i=0;i<8;i++)
            {
                for(int j=0;j<8;j++)
                {
                    if(p->tablero_estado[i][j] == p->m_player)
                        cont_p1++;
                    else if(p->tablero_estado[i][j]!=0)
                        cont_p2++;
                }
            }
            return cont_p1 - cont_p2;
        }

        ///devuelve un int que es el indice del hijo de root que se debe elegir
        int camino(CNode *p )
        {
            if(p->nivel == nivel_max) return min_max(p);
            vector<int> val;

            for(int i=0;i<p->c_hijos.size();i++)
                val.push_back(camino(p->c_hijos[i]));
            int loco;
            if( p->nivel == ia_color)
                loco = maximo(val);
            else
                loco = minimo(val);
            return loco;
        }


        int maximo(vector<int> arr)
        {
            int mayor;
            mayor = 0;
            for(int i=1;i<arr.size();i++)
                if(arr[i]> arr[mayor])
                    mayor = i;

            return mayor;
        }
        int minimo(vector<int> arr)
        {
            int minimo;
            minimo = 0;
            for(int i=1;i<arr.size();i++)
                if(arr[i]<arr[minimo])
                    minimo = i;

            return minimo;
        }



       // virtual ~CNTree();
};

#endif / / CNTREE_H
