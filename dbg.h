#pragma once
#include <bits/stdc++.h>
using namespace std;
#define dbg(...) __f(#__VA_ARGS__,__VA_ARGS__)

// ---- forward declarations (so nested containers resolve regardless of
// definition order below, e.g. map<int, vector<int>> or vector<list<int>>) ----
template<class L,class R> std::ostream& operator<<(std::ostream& os,std::pair<L,R>& P);
template<class T> std::ostream& operator<<(std::ostream& os,std::vector<T>& V);
template<class T> std::ostream& operator<<(std::ostream& os,std::list<T>& L);
template<class L,class R> std::ostream& operator<<(std::ostream& os,std::map<L,R>& MP);
template<class L,class R> std::ostream& operator<<(std::ostream& os,std::unordered_map<L,R>& MP);
template<class T> std::ostream& operator<<(std::ostream& os,std::set<T>& S);
template<class T> std::ostream& operator<<(std::ostream& os, std::set<T, std::greater<T>>& S);
template<class T> std::ostream& operator<<(std::ostream& os,std::unordered_set<T>& S);
template<class T> std::ostream& operator<<(std::ostream& os,std::multiset<T>& S);
template<class T> std::ostream& operator<<(std::ostream& os, std::multiset<T, std::greater<T>>& S);
template<class T> std::ostream& operator<<(std::ostream& os,std::stack<T> st);
template<class T> std::ostream& operator<<(std::ostream& os,std::queue<T> q);
template<class T> std::ostream& operator<<(std::ostream& os, std::deque<T>& D);
template<class T, size_t S> std::ostream& operator<<(std::ostream& os,std::array<T, S> V);
template<class T> std::ostream& operator<<(std::ostream& os, std::priority_queue<T> pq);
template<class T> std::ostream& operator<<(std::ostream& os, std::priority_queue<T, std::vector<T>, std::greater<T>> pq);

// trace std::pair
template<class L,class R> std::ostream& operator<<(std::ostream& os,std::pair<L,R>& P){
	return os<<"{"<<P.first<<":"<<P.second<<"}";
}
// trace std::vector
template<class T> std::ostream& operator<<(std::ostream& os,std::vector<T>& V){
	os<<"[ ";for(auto v:V)os<<v<<" ";return os<<"]";
}
// trace std::list
template<class T> std::ostream& operator<<(std::ostream& os,std::list<T>& L){
	os<<"[ ";for(auto v:L)os<<v<<" ";return os<<"]";
}
// trace std::map;
template<class L,class R> std::ostream& operator<<(std::ostream& os,std::map<L,R>& MP) {
	os<<"[ ";for(auto& P : MP) os<<P<<" ";return os<<"]";
}
// trace unordred_std::map
template<class L,class R> std::ostream& operator<<(std::ostream& os,std::unordered_map<L,R>& MP) {
	os<<"[ ";for(auto& P : MP) os<<P<<" ";return os<<"]";
}
// trace std::set
template<class T> std::ostream& operator<<(std::ostream& os,std::set<T>& S){
	os<<"[ ";for(auto s:S)os<<s<<" ";return os<<"]";
}
// Debugging for std::set<int, std::greater<int>> (custom comparator)
template<class T>
std::ostream& operator<<(std::ostream& os, std::set<T, std::greater<T>>& S) {
	os << "[ ";
	for (auto s : S) os << s << " ";
	return os << "]";
}
// trace std::unordered_set
template<class T> std::ostream& operator<<(std::ostream& os,std::unordered_set<T>& S){
	os<<"[ ";for(auto s:S)os<<s<<" ";return os<<"]";
}
// trace std::multiset
template<class T> std::ostream& operator<<(std::ostream& os,std::multiset<T>& S){
	os<<"[ ";for(auto s:S)os<<s<<" ";return os<<"]";
}
// Debugging for std::set<int, std::greater<int>> (custom comparator)
template<class T>
std::ostream& operator<<(std::ostream& os, std::multiset<T, std::greater<T>>& S) {
	os << "[ ";
	for (auto s : S) os << s << " ";
	return os << "]";
}
// std::stack FUN
template <class T>
void F_Stack(std::stack<T> st, std::string& cont) {
	if (st.empty()) return;
	T mem = st.top();
	st.pop();
	F_Stack(st, cont);
	// Use stringstream to handle any type T
	std::stringstream ss;
	ss << mem;
	cont += " " + ss.str();
}
// trace std::stack                                                  
template<class T> std::ostream& operator<<(std::ostream& os,std::stack<T> st) {
	os<<"[";std::string cont="";F_Stack(st,cont);return os<<cont<<" ]";
}
// track std::queue
template<class T> std::ostream& operator<<(std::ostream& os,std::queue<T> q) {
	os<<"[ ";while(!q.empty()) os<<q.front()<<" ",q.pop();return os<<"]";
}
// Debugging for std::deque
template<class T>
std::ostream& operator<<(std::ostream& os, std::deque<T>& D) {
	os << "[ ";
	for (auto& d : D) os << d << " ";
	return os << "]";
}
// dbg std::std::array
template<class T, size_t S> std::ostream& operator<<(std::ostream& os,std::array<T, S> V){
	os<<"[ ";for(auto v:V)os<<v<<" ";return os<<"]";
}
// Debugging for max-heap (default priority queue)
template <class T>
void F_PriorityQueue(std::priority_queue<T> pq, std::string& cont) {
	while (!pq.empty()) {
		T mem = pq.top();
		pq.pop();
		
		// Use stringstream for general types
		std::stringstream ss;
		ss << mem;
		cont += " " + ss.str();
	}
}

// Debugging for min-heap (custom comparator)
template <class T>
void F_MinPriorityQueue(std::priority_queue<T, std::vector<T>, std::greater<T>> pq, std::string& cont) {
	while (!pq.empty()) {
		T mem = pq.top();
		pq.pop();
		
		// Use stringstream for general types
		std::stringstream ss;
		ss << mem;
		cont += " " + ss.str();
	}
}

// Debug function for priority queue (max-heap)
template<class T>
std::ostream& operator<<(std::ostream& os, std::priority_queue<T> pq) {
	os << "[";
	std::string cont = "";
	F_PriorityQueue(pq, cont);
	return os << cont << " ]";
}

// Debug function for min-heap priority queue
template<class T>
std::ostream& operator<<(std::ostream& os, std::priority_queue<T, std::vector<T>, std::greater<T>> pq) {
	os << "[";
	std::string cont = "";
	F_MinPriorityQueue(pq, cont);
	return os << cont << " ]";
}


// for last arg.
template<typename Arg1>
void __f(const char* name,Arg1&& arg1){
	std::cerr<<name<<" : "<<arg1<<std::endl;
}
// for variable arg
template <typename Arg1,typename... Args>
void __f(const char* names,Arg1&& arg1,Args&&... args){
	const char* comma=strchr(names+1,',');std::cerr.write(names,comma-names)<<" : "<<arg1<<" | ";__f(comma+1,args...);
}
