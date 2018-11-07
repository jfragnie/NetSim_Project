#include "network.h"
#include "random.h"
#include <utility>
#include <iostream>
#include <functional>

void Network::resize(const size_t& nb) {	
	RandomNumbers randomnum;
	for (size_t i(0); i < nb; ++i) {
		values.push_back(0);
	}
	randomnum.normal(values, 0, 1);  
}

bool Network::add_link(const size_t& nodea, const size_t& nodeb) {	
	
	if ((nodea == nodeb) or (size() <= nodea) or (size() <= nodeb))
		
		return false;
	for (auto it : links) {
		if (it.first == nodea) {
			if (it.second == nodeb) 
				return false;
		}
		if (it.first == nodeb) {
			if (it.second == nodea) 
				return false;	
		}
	}
	links.insert(std::make_pair(nodea, nodeb));
	links.insert(std::make_pair(nodeb, nodea));
	return true;
}


size_t Network::random_connect(const double& mean_deg) {
	links.clear();	
	RandomNumbers randomNum;
	unsigned int count(0);
	std::vector<size_t> reservoir;
	for (size_t i(0); i < values.size(); ++i)  {  
		reservoir.push_back(i);
	}
	for (size_t i(0); i < values.size(); ++i)  {  
	
		unsigned int deg(randomNum.poisson(mean_deg));
		unsigned int num(0);
		while (num < deg)  {
			randomNum.shuffle(reservoir);
			if (add_link(i, reservoir[0])) {
				++num;
				++count;
			}
		}
	}
	return count;
}

size_t Network::set_values(const std::vector<double>& newVAL) {	
	if (newVAL.empty()) {
		return 0;
	} 
	if (newVAL.size() < values.size()) {
		for (size_t i(0); i < newVAL.size(); ++i) {	
				values[i] = newVAL[i];
		}
	}
	else {
		values.clear();
		for (size_t i(0); i < newVAL.size(); ++i)  {
			values.push_back(newVAL[i]);
		}
	}
	return newVAL.size();
}

size_t Network::size() const {
	return values.size();
}

size_t Network::degree(const size_t & node) const {
	size_t count(0);
	for (auto it : links)  {
		if (it.first == node)  {
		  ++count;	
		}
	}
	return count;
}

double Network::value(const size_t & node) const {
	if (node <= size())
		return values[node];	
	else return 0;
}

std::vector<double> Network::sorted_values() const {
	std::vector<double> sorted(values);
	std::sort(sorted.begin(), sorted.end(), std::greater<double>());
	return sorted;	
}

std::vector<size_t> Network::neighbors(const size_t& node) const {
	std::vector<size_t> link;
	for (auto it : links) {
		if (it.first == node) {
			link.push_back(it.second);	
		}	
	}	
	return link;
}
