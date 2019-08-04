#include <iostream>
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include <stdlib.h>
#include <string>
#include <curl/curl.h>
using namespace std;
using namespace rapidjson;



std::string buffer;

size_t curl_write( void *ptr, size_t size, size_t nmemb, void *stream)
{
	buffer.append((char*)ptr, size*nmemb);
	return size*nmemb;
}

int main()
{
	string tmptitle,title,url,opcao,stype;

		while(1)
		{
			cin >> opcao;
	
			if (opcao == "-h")
			{
				cout << "\n-h   --Help";
				cout << "\n-s   --Serach";
				cout << "\n-t   --Type";
			}
			
			if(opcao == "-t")
			{
				if(tmptitle == "")
				{
					cout<<"\nNenhum titulo selecionado. ";
					continue;
				}
				else
				{
					cout<<"Tipo: " <<stype << "\n"; 
				}	
					
			}
			
			
			if (opcao == "-s")
			{
				
				CURL *curl;
				CURLcode res;
				int start,i;
				cout<<"\nDigite o titulo do filme: ";
				getline (std::cin,tmptitle); 
				
				if(tmptitle=="")
				{ 
					continue;
				}
				
				start = 0;
				//substituir espaços por %2f
				for(i=0;i<tmptitle.length();i++)
				{
					if(tmptitle[i] == ' ')
					{	
						title.append(tmptitle,start,i-start);
						title = title+"%2f";
						start = i+1;
					}
				}	
					
				title.append(tmptitle,start,i-start);
				curl = curl_easy_init();
				//URL da api + titulo
				url = "http://www.omdbapi.com/?t="+title+"&plot=full"; 
				
				//Menssagem de buscando
				cout<<"\nBuscando: "<<tmptitle<<"\n";
				cout<<"\nAguarde...\n\n";
				
				if(curl) 
				{
					//Setando URL
					curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
					curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
					curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, curl_write);
					res = curl_easy_perform(curl);
					//Buscando erro
					if(res != CURLE_OK)
					{
						fprintf(stderr, "curl_easy_perform() Erro: %s\n",curl_easy_strerror(res));
					}
					
					try
					{	
						
						if(buffer.length()<100)
						{ 
							cout<<"Erro: Titulo não encontrado!\n";
						}
						else
						{
							// Variaveis de teorno
							const char* json = buffer.c_str();
							Document d;
							d.Parse(json);
							Value& name = d["Title"];
							Value& year = d["Year"];
							Value& rated = d["Rated"];
							Value& released = d["Released"];
							Value& runtime = d["Runtime"];
							Value& genre = d["Genre"];
							Value& director = d["Director"];
							Value& writer = d["Writer"];
							Value& actors = d["Actors"];
							Value& plot = d["Plot"];
							Value& language = d["Language"];
							Value& country = d["Country"];
							Value& awards = d["Awards"];
							Value& poster = d["Poster"];
							Value& ratings = d["Ratings"];
							Value& internet = d["Internet Movie Database"];
							Value& rotten = d["Rotten Tomatoes"];
							Value& meta = d["Metacritic"];
							Value& type = d["Type"];
							Value& dvd = d["DVD"];
							Value& box = d["BoxOffice"];							
							Value& production = d["Production"];
							Value& site = d["Website"];
							
							
							
							
							// Imprimindo resultados
							
							cout<<"Titulo: "<<name.GetString()<<" - "<<year.GetString()<<endl;
							cout<<"Ano: "<<year.GetString()<<endl;
							cout<<"Avaliaçao: "<<rated.GetString()<<endl;
							cout<<"Lançamento: "<<released.GetString()<<endl;
							cout<<"Tempo: "<<runtime.GetString()<<endl;
							cout<<"Genero: "<<genre.GetString()<<endl;
							cout<<"Director: "<<director.GetString()<<endl;
							cout<<"Escritor: "<<writer.GetString()<<endl;
							cout<<"Atores: "<<actors.GetString()<<endl;
							cout<<"Enredo: "<<plot.GetString()<<endl;
							cout<<"Lingua: "<<language.GetString()<<endl;
							cout<<"País: "<<country.GetString()<<endl;
							cout<<"Prêmios: "<<awards.GetString()<<endl;
							cout<<"Poster: "<<poster.GetString()<<endl;
							cout<<"Classificações: "<<ratings.GetString()<<endl;
							cout<<"Banco de dados na internet: "<<internet.GetString()<<endl;
							cout<<"Rotten Tomatoes: "<<rotten.GetString()<<endl;
							cout<<"Metacritic: "<<meta.GetString()<<endl;
							cout<<"Tipo: "<<type.GetString()<<endl;
							stype = type.GetString();
							cout<<"DVD: "<<dvd.GetString()<<endl;
							cout<<"Bilheteria: "<<box.GetString()<<endl;							
							cout<<"Produtora: "<<production.GetString()<<endl;
							cout<<"Site: "<<site.GetString()<<endl;
							
						}
					}
					
					catch(...)
					{ 
						cout<<"Erro ao conectar, tente novamente mais tarde!";
					}
					
					buffer.clear();
					curl_easy_cleanup(curl);
					title.erase(title.begin(),title.end());
				}
			}
		}
		return 0;
	}
