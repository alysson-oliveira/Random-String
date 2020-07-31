#include <bits/stdc++.h>
using namespace std;

#define POPULATION_SIZE 1000 // Quantidade de indivíduos em cada geração

// Caracteres válidos, ou seja, genes a serem considerados
const string GENES = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ 1234567890, .-;:_!\"#%&/()=?@${[]}";

const string TARGET = "SSC0713 - Sistemas Evolutivos Aplicados a Robotica";    // String objetivo

int random_num(int start, int end){  // Função para gerar números aleatórios
	int range = (end-start)+1;
	int random_int = start+(rand()%range);
	return random_int;
}

char mutated_genes(){    // Gera genes aleatórios para realizar a mutação
	int len = GENES.size();
	int r = random_num(0, len-1);
	return GENES[r];
}


string create_genes(){   // Cria a string de genes
	int len = TARGET.size();
	string rstring = "";
	for(int i = 0;i<len;i++)
		rstring += mutated_genes();
	return rstring;
}

class Individual{   // Classe utilizada para representar cada indivíduo da população
public:
	string chromosome;
	int fitness;
	Individual(string chromosome);
	Individual mate(Individual parent2);
	int calculate_fitness();
};

Individual::Individual(string chromosome){  // Adiciona um indivíduo
	this->chromosome = chromosome;
	fitness = calculate_fitness();
};

Individual Individual::mate(Individual par2){    // Gera novos descendentes baseados nos pais
	string child_chromosome = "";   // Variável para armazenar os cromossomos dos descendentes

	int len = chromosome.size();    // Recebe a quantidade de cromossomos
	for(int i = 0;i<len;i++){
		float p = random_num(0, 100)/100;   // Recebe um valor aleatório entre 0 e 1
		if(p < 0.45)                        // Insere o gene do indivíduo 1 se o valor for menor que 0,45
			child_chromosome += chromosome[i];
		else if(p < 0.90)   // Insere o gene do indivíduo 2 se o valor estiver entre 0,45 e 0,90
			child_chromosome += par2.chromosome[i];
		else            // Gera mutação de genes caso o valor seja maior que 0,90 através da função mutated_genes()
			child_chromosome += mutated_genes();
	}
	return Individual(child_chromosome);    // Retorna o descendente resultante
};

int Individual::calculate_fitness(){   // Calcula o fitness, que representa a quantidade de caracteres que diferem da string objetivo
	int len = TARGET.size();
	int fitness = 0;
	for(int i = 0;i<len;i++)
	{
		if(chromosome[i] != TARGET[i])
			fitness++;
	}
	return fitness;
};

bool operator<(const Individual &ind1, const Individual &ind2){  // Função para obter qual indivíduo possui maior fitness
	return ind1.fitness < ind2.fitness;
}

int main(){
	srand((unsigned)(time(0)));
	int generation = 0; 	// Geração atual

	vector<Individual> population;  // Vetor contendo a população
	bool found = false;

	for(int i = 0;i<POPULATION_SIZE;i++){    // Cria a população inicial
		string rstring = create_genes();
		population.push_back(Individual(rstring));
	}

	while(! found){
		sort(population.begin(), population.end());      // Organiza o vetor população em ordem crescente de fitness
		if(population[0].fitness <= 0){  // Caso o primeiro indivíduo possua fitness zero, significa que encontramos a solução
			found = true;
			break;      // Encerra o Loop principal
		}
		vector<Individual> new_generation;  // Gera descendentes para a nova geração

		// Seleciona os 10% melhores indivíduos da população atual, baseando-se no fitness, para comporem a próxima geração (sobrevivência do mais forte)
		int s = (10*POPULATION_SIZE)/100;
		for(int i = 0;i<s;i++)
			new_generation.push_back(population[i]);

		// Seleciona os 50% melhores indivíduos da população atual, baseando-se no fitness, para gerarem novos descendentes
		s = (90*POPULATION_SIZE)/100;
		for(int i = 0;i<s;i++){
			int len = population.size();
			int r = random_num(0, 50);      // Indivíduo 1 aleatório dos melhores 50%
			Individual parent1 = population[r];
			r = random_num(0, 50);          // Indivíduo 2 aleatório dos melhores 50%
			Individual parent2 = population[r];
			Individual offspring = parent1.mate(parent2);
			new_generation.push_back(offspring);
		}

		population = new_generation;        // Atualiza a geração
		cout<< "Generation: " << generation << "\t";
		cout<< "String: "<< population[0].chromosome <<"\t";
		cout<< "Fitness: "<< population[0].fitness << "\n";
		generation++;
	}

	// Printa o resultado obtido
	cout<< "Generation: " << generation << "\t";
	cout<< "String: "<< population[0].chromosome <<"\t";
	cout<< "Fitness: "<< population[0].fitness << "\n";
}
