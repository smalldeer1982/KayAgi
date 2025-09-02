# [GCJ 2016 Finals] Integeregex

## 题目描述

在本题中，一个合法的正则表达式是下列之一。描述中的 $E_1, E_2$ 等表示（不一定不同的）合法正则表达式。

* 一个十进制数字：即 $\mathbf{0}\ \mathbf{1}\ \mathbf{2}\ \mathbf{3}\ \mathbf{4}\ \mathbf{5}\ \mathbf{6}\ \mathbf{7}\ \mathbf{8}\ \mathbf{9}$ 之一。
* 连接：$E_1 E_2$。
* 并选：$\left(E_1|E_2|\ldots|E_N\right)$，其中至少有两个表达式。注意外层括号是必须的。
* 重复：$\left(E_1\right)^*$。注意外层括号是必须的。

例如，$7$, $23$, $(7)^*$, $(45)^*$, $(1|2|3)$, $((2)^*|3)$, $(1|2|3)$, $((0|1))^*$ 都是合法表达式。$(7)$, $4|5$, $4^*$, $(1|)$, $(0|1)^*$ 都不是。

我们说表达式 $E$ 匹配数字字符串 $D$ 当且仅当下列之一成立：

* $E=D$。
* $E=E_1 E_2$，且存在 $D_1, D_2$ 使得 $D=D_1 D_2$ 且 $E_i$ 匹配 $D_i$。
* $E=\left(E_1|E_2|\ldots|E_N\right)$，且至少有一个 $E_i$ 匹配 $D$。
* $E=\left(E_1\right)^*$，且存在若干非负整数 $N$ 及 $D_1, D_2, \ldots, D_N$，使得 $D=D_1 D_2 \ldots D_N$ 且 $E_1$ 匹配每个 $D_i$。特别地，$\left(E_1\right)^*$ 匹配空串。

例如，表达式 $((1|2))^*3$ 匹配 $3, 13, 123, 2221123$ 等字符串，但不匹配 $1234, 3123, 12, 33$ 等。

给定一个合法的正则表达式 $\mathbf{R}$，问有多少个整数在 $[\mathbf{A}, \mathbf{B}]$ 间，其十进制表示（无前导零）能被 $\mathbf{R}$ 匹配？

## 说明/提示

**样例解释**

注意，样例 5 至 8 不会出现在小数据集中。

在样例 1 中，区间内匹配的数字为 $1, 10, 100, 1000$。

在样例 2 中，区间内匹配的数字为 $379009$。

在样例 3 中，区间内匹配的数字为 $12, 34, 1212, 1234, 3434$。

在样例 4 中，没有匹配的数字。

在样例 5 中，区间内匹配的数字为 $1, 10, 11, 100$。

在样例 6 中，区间内匹配的数字为 $23, 45$。

在样例 7 中，区间内的任意数字都能被匹配。

在样例 8 中，区间内匹配的数字为 $1, 19, 156, 179, 189, 199$。

**限制条件**

- $1 \leqslant \mathbf{T} \leqslant 100$。
- $1 \leqslant \mathbf{A} \leqslant \mathbf{B} \leqslant 10^{18}$。
- $1 \leqslant \mathbf{R}$ 的长度 $\leqslant 30$。

**小数据集（15 分，测试集 1 - 可见）**

- $\mathbf{R}$ 不包含 | 字符。

**大数据集（15 分，测试集 2 - 隐藏）**

- 无其他限制。

翻译由 GPT4.1 完成。

## 样例 #1

### 输入

```
8
1 1000
(0)*1(0)*
379009 379009
379009
1 10000
(12)*(34)*
4 5
45
1 100
((0|1))*
1 50
(01|23|45|67|23)
1 1000000000000000000
((0|1|2|3|4|5|6|7|8|9))*
1 1000
1(56|(((7|8))*9)*)```

### 输出

```
Case #1: 4
Case #2: 1
Case #3: 5
Case #4: 0
Case #5: 4
Case #6: 2
Case #7: 1000000000000000000
Case #8: 6```

# 题解

## 作者：bcdmwSjy (赞：6)

超级数位 dp 题，建议评黑。

题目让我们求出 $l$ 到 $r$  范围内能匹配上给定的正则表达式的数字的数量，正则表达式中只有数字、或（`|`）、克林闭包（`*`）和括号。

做这个题之前先确保你会做 P3311，那道题是在 AC 自动机上计算数位 dp。

我们考虑如何匹配一个正则表达式，我们可以使用 Thompson 构造法使正则表达式转换为 NFA（非确定有限状态机）。

Thompson 算法的核心思想是递归地构建 NFA 片段，然后通过连接、或、闭包等操作组合这些片段。

NFA 的状态和转移：

- 每个 NFA 片段有一个开始状态和一个接受状态。
  
- 转移可以是字符或者 $\varepsilon$（空转移）。

步骤：

1. 我们将正则表达式转换为后缀表达式，以便于处理运算符优先级。

   注意：我们需要处理运算符的优先级和括号。优先级：括号 > 克林闭包 > 连接（隐式的）> 或。

   在正则表达式中，连接是隐式的（例如：ab 表示 a 连接 b），所以我们需要在适当的位置插入连接符（用 `~` 表示连接符）。

2. 将中缀表达式转换为后缀表达式。

3. 使用栈来构建 NFA：遍历后缀表达式，遇到字符则创建简单的 NFA（两个状态，一个转移），遇到运算符则从栈中弹出操作数（一个或两个）并应用运算符，然后将新的 NFA 片段压入栈中。

具体操作：

- 对于单个字符 c：构建两个状态（start 和 end），中间有一条标记为 c 的边。

- 对于连接：弹出两个 NFA 片段（先弹出的是右侧，后弹出的是左侧）。将左侧的接受状态与右侧的开始状态用 $\varepsilon$ 边连接，新的开始状态为左侧的开始状态，新的接受状态为右侧的接受状态。

- 对于或运算：弹出两个 NFA 片段（假设为 a 和 b）。新建开始状态和接受状态。从开始状态 $\varepsilon$ 转移到 a 和 b 的开始状态；a 和 b 的接受状态 $\varepsilon$ 转移到新的接受状态。注意，a 和 b 的接受状态将不再是接受状态。

- 对于克林闭包：弹出一个 NFA 片段（假设为 a）。新建开始状态和接受状态。从新的开始状态 $\varepsilon$ 转移到 a 的开始状态以及新的接受状态；从 a 的接受状态 $\varepsilon$ 转移到 a 的开始状态和新的接受状态。

这种算法求出的 NFA 虽然 $\varepsilon$ 边较多，但是符合 NFA 的要求。

我们可以写出以下代码：

```cpp
struct State{
	int id;
	map<char,vector<State*>> transitions;
};

struct Fragment{
	State* start;
	State* accept;
};

struct RegexToNFA{
	int stateCounter=0;
	vector<State*> allStates;

	State* createState(){
		State* state=new State{stateCounter++};
		allStates.push_back(state);
		return state;
	}

	void addTransition(State* from,State* to,char c){
		from->transitions[c].push_back(to);
	}

	string insertConcat(const string& re){
		string result;
		for (int i=0;i<int(re.length());i++){
			char c=re[i];
			result+=c;
			if (i<int(re.length())-1){
				char next=re[i+1];
				if ((isalnum(c) or c=='*' or c==')') and (isalnum(next) or next=='(')){
					result.push_back('~');
				}
			}
		}
		return result;
	}

	int precedence(char op){
		if (op=='|') return 1;
		else if (op=='~') return 2;
		else if (op=='*') return 3;
		else return 0;
	}

	string infixToPostfix(const string& re){
		stack<char> s;
		string postfix;
		for (char c:re){
			if (isalnum(c)){
				postfix+=c;
			}else if (c=='('){
				s.push(c);
			}else if (c==')'){
				for (;not s.empty() and s.top()!='(';s.pop()) postfix+=s.top();
				if (not s.empty() and s.top()=='(') s.pop();
			}else{
				for (;not s.empty() and precedence(s.top())>=precedence(c);s.pop()) postfix+=s.top();
				s.push(c);
			}
		}
		for (;not s.empty();s.pop()) postfix+=s.top();
		return postfix;
	}

	RegexToNFA()=default;

	~RegexToNFA(){
		for (State* state:allStates) delete state;
	}

	Fragment buildNFA(const string& re){
		string withConcat=insertConcat(re);
		string postfix=infixToPostfix(withConcat);
		stack<Fragment> s;

		for (char c:postfix){
			if (c=='~'){
				Fragment frag2=s.top();s.pop();
				Fragment frag1=s.top();s.pop();
				addTransition(frag1.accept,frag2.start,'\0');
				s.push({frag1.start,frag2.accept});
			}else if (c=='|'){
				Fragment frag2=s.top();s.pop();
				Fragment frag1=s.top();s.pop();
				State* start=createState();
				State* accept=createState();
				addTransition(start,frag1.start,'\0');
				addTransition(start,frag2.start,'\0');
				addTransition(frag1.accept,accept,'\0');
				addTransition(frag2.accept,accept,'\0');
				s.push({start,accept});
			}else if (c=='*'){
				Fragment frag=s.top();s.pop();
				State* start=createState();
				State* accept=createState();
				addTransition(start,frag.start,'\0');
				addTransition(start,accept,'\0');
				addTransition(frag.accept,frag.start,'\0');
				addTransition(frag.accept,accept,'\0');
				s.push({start,accept});
			}else{
				State* start=createState();
				State* accept=createState();
				addTransition(start,accept,c);
				s.push({start,accept});
			}
		}
		return s.top();
	}
};
```

接下来，我们实际上很难在 NFA 上进行 dp，因为 NFA 匹配时可能有多条路径可以走，需要递归处理，这不利于我们进行数位 dp。

我们考虑把 NFA 转成 DFA（确定有限自动机），这样就不需要递归，一直沿着转移边往下走就行了。

要将 NFA 转换为 DFA，我们使用子集构造法。基本思想是：DFA 的每个状态是 NFA 状态的一个子集。转换时，对于每个输入字符，计算当前状态子集的 $\varepsilon$ 闭包，然后通过该字符转换，再求 $\varepsilon$ 闭包，得到下一个状态子集。

步骤：

1. 计算 $\varepsilon$ 闭包：给定一个状态集合 S，$\varepsilon$ 闭包是从 S 中的状态通过任意条 $\varepsilon$ 转换可以到达的所有状态的集合。

2. 初始化：从 NFA 的起始状态的 $\varepsilon$ 闭包开始，作为 DFA 的起始状态。

3. 对于每个 DFA 状态（即一个 NFA 状态集合）和每个输入字符（不包括 $\varepsilon$，因为 DFA 没有 $\varepsilon$ 转换）：

    a. 计算从该状态集合中的每个状态通过该字符转换所能到达的状态的集合（不包含 $\varepsilon$ 转换）。

    b. 然后计算这个集合的 $\varepsilon$ 闭包。

    c. 如果得到的集合非空且未在 DFA 中出现过，则将其加入 DFA 状态集合。

    d. 添加 DFA 转换：从当前状态（集合）通过该字符转换到新状态（集合）。

4. 标记接受状态：如果 DFA 状态（一个集合）中包含 NFA 的任何一个接受状态，则该 DFA 状态为接受状态。

代码如下：

```cpp
struct DFAState{
	int id;
	set<State*> nfaStates;
	map<char,DFAState*> transitions;
	bool isAccept=false;

	DFAState(int id,const set<State*>& states):id(id),nfaStates(states){}
};

struct NFAToDFA{
	Fragment nfa;
	set<char> alphabet;
	vector<DFAState*> dfaStates;
	map<set<State*>,DFAState*> stateSetMap;
	int stateCounter=0;

	set<State*> epsilonClosure(const set<State*>& states){
		stack<State*> s;
		set<State*> closure=states;

		for (State* sta:states) s.push(sta);

		while (not s.empty()){
			State* t=s.top();
			s.pop();
			auto it=t->transitions.find('\0');
			if (it!=t->transitions.end()){
				for (State* u:it->second){
					if (closure.find(u)==closure.end()){
						closure.insert(u);
						s.push(u);
					}
				}
			}
		}
		return closure;
	}

	set<State*> move(const set<State*>& states,char c){
		set<State*> next;
		for (State* s:states){
			auto it=s->transitions.find(c);
			if (it!=s->transitions.end()){
				for (State* t:it->second){
					next.insert(t);
				}
			}
		}
		return next;
	}

	set<State*> moveEpsilonClosure(const set<State*>& states,char c){
		set<State*> next=move(states,c);
		return epsilonClosure(next);
	}

	void extractAlphabet(){
		set<State*> visited;
		stack<State*> stack;
		stack.push(nfa.start);
		visited.insert(nfa.start);

		while (not stack.empty()){
			State* state=stack.top();
			stack.pop();
			for (auto& trans:state->transitions){
				char symbol=trans.first;
				if (symbol!='\0' and symbol!='~') alphabet.insert(symbol);
				for (State* next:trans.second){
					if (visited.find(next)==visited.end()){
						visited.insert(next);
						stack.push(next);
					}
				}
			}
		}
	}

	NFAToDFA(Fragment nfaFragment):nfa(nfaFragment){
		extractAlphabet();
	}

	~NFAToDFA(){
		for (DFAState* state:dfaStates) delete state;
	}

	void convert(){
		set<State*> startSet;
		startSet.insert(nfa.start);
		set<State*> startClosure=epsilonClosure(startSet);

		DFAState* startState=new DFAState(stateCounter++,startClosure);
		startState->isAccept=(startClosure.find(nfa.accept)!=startClosure.end());
		dfaStates.push_back(startState);
		stateSetMap[startClosure]=startState;

		queue<DFAState*> q;
		q.push(startState);

		while (not q.empty()){
			DFAState* curr=q.front();
			q.pop();

			for (char c:alphabet){
				set<State*> nextSet=moveEpsilonClosure(curr->nfaStates,c);
				if (nextSet.empty()) continue;

				DFAState* nextState=nullptr;
				if (stateSetMap.find(nextSet)==stateSetMap.end()){
					nextState=new DFAState(stateCounter++,nextSet);
					nextState->isAccept=(nextSet.find(nfa.accept)!=nextSet.end());
					dfaStates.push_back(nextState);
					stateSetMap[nextSet]=nextState;
					q.push(nextState);
				}else{
					nextState=stateSetMap[nextSet];
				}

				curr->transitions[c]=nextState;
			}
		}
	}
};
```

在 DFA 上匹配字符串非常简单，只需要从起始状态一直走，遍历完整个字符串后看当前状态是不是接受状态。

```cpp
bool match(const NFAToDFA& dfa,const string& s){
	int p=0;
	for (auto c:s){
		bool flag=true;
		for (auto& trans:dfa.dfaStates[p]->transitions){
			if (trans.first==c){
				p=trans.second->id;
				flag=false;
				break;
			}
		}
		if (flag) return false;
	}
	return dfa.dfaStates[p]->isAccept;
}
```

接下来考虑数位 dp 部分，我们使用记忆化搜索实现，搜索时记录当前匹配了到 DFA 上的哪一个节点，到达边界时看是不是匹配到了接受节点。

```cpp
int a[20];
ll f[20][1000][2][2]; // DFA 应该不会超过 1000 个点，毕竟正则表达式长度最多只有 30 个字符

ll dfs(int len,int u,int op,int lim,const NFAToDFA& dfa){
	if (len==0) return op==0 and dfa.dfaStates[u]->isAccept;
	if (f[len][u][op][lim]!=-1) return f[len][u][op][lim];
	int maxn=(lim?a[len]:9);
	ll ans=0;
	for (int i=0;i<=maxn;i++){
		if (i==0 and op){ // 前导零直接往下走
			ans+=dfs(len-1,u,op and i==0,lim and i==maxn,dfa);
		}else{
			for (auto& trans:dfa.dfaStates[u]->transitions){
				if (trans.first==char(i+'0')){
					ans+=dfs(len-1,trans.second->id,op and i==0,lim and i==maxn,dfa);
					break;
				}
			}
		}
	}
	return f[len][u][op][lim]=ans;
}

ll solve(ll x,const NFAToDFA& dfa){
	memset(f,-1,sizeof(f));
	int len=0;
	do{
		a[++len]=x%10;
		x/=10;
	}while (x);
	return dfs(len,0,1,1,dfa);
}

int main(){
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	int T;
	cin>>T;
	for (int t=1;t<=T;t++){
		ll l,r;
		string re;
		cin>>l>>r>>re;
		RegexToNFA nfaConverter;
		Fragment nfa=nfaConverter.buildNFA(re);

		NFAToDFA dfa(nfa);
		dfa.convert();
		cout<<"Case #"<<t<<": "<<solve(r,dfa)-solve(l-1,dfa)<<"\n";
	}
	return 0;
}
```

代码总共近 7k，不过跑的相当快，一个点不到 15ms 就能计算完毕。

---

