# Arithmancy (Medium)

## 题目描述

本题不同版本的区别仅在于 $n$ 的最大值。

Vector 教授在为她的算术课做准备，她需要准备 $n$ 个独特的魔法单词。每一个魔法单词都是由字符 X 和 O 组成的字符串。学生需要将两个魔法单词拼接在一起组成一个咒语，而咒语的力量（Power）定义为其所有不同的非空子串的数量。例如，咒语 XOXO 的力量为 7，因为它包括 7 个不同的子串：X, O, XO, OX, XOX, OXO 和 XOXO。

每位学生将独立随机地从 Vector 教授提供的 $n$ 个单词中挑选两个单词拼接形成自己的咒语，这意味着可能选择到两个完全相同的单词。然后学生计算出他们咒语的力量，并报告给 Vector 教授。为了检查学生们的计算结果并展示她的能力，Vector 教授需要知道每位学生拼接的具体是哪两个魔法单词以及它们的顺序。

你的任务就是扮演 Vector 教授：首先，创建 $n$ 个互不相同的魔法单词；接着，根据多次请求，通过已知的咒语力量来确定学生使用的两个单词索引及其顺序。

## 说明/提示

- 1 ≤ n ≤ 30
- 1 ≤ q ≤ 1000
- 魔法单词长度在 1 到 $30 \cdot n$ 之间。

 **本翻译由 AI 自动生成**

## 样例 #1

### 输入

```
2


2
15

11```

### 输出

```
XOXO
X


1 1

2 1```

# 题解

## 作者：FFTotoro (赞：4)

[点这里前往游记。](https://www.luogu.com.cn/article/u3edqf6r)

场切了这个 $\color{Red}*2600$，太舒服了。自从来了某学校，卡时、假算、乱搞能力显著增强；不过这题乱搞似乎就是真算。

建议先阅读 [D1 题解](https://www.luogu.com.cn/article/q26rotbj)。

我们沿用 D1 的做法，考虑随机一堆字符串然后打表。但是因为 $n$ 比较大，所以 $f(w_i+w_j)$ 有极大的概率会重复一些。由于这题 $n\le 30$，下文若无特殊说明则将 $n$ 视为 $30$。

但是题面有说，交互库的询问方式是每次**均匀随机**选择两个下标 $(i,j)(1\le i,j\le n)$ 问。于是可以得出，只要重复的 $(i,j)$ 的数量不太多，$1000$ 次询问是可以过去的。

考虑均匀随机地生成那些字符串。这样直接干肯定是过不去的，于是我们考虑加入如下的若干技巧，使得随机可以通过题目：

- 虽然说长度限制为 $900$，但是并不是让每个字符串长度都达到 $900$，这样反而不优：我们控制每个字符串的长度在 $[450,900]$ 之间即可——如果 $n<30$ 就类似地把长度控制在 $[15n,30n]$ 之间；
- 时限很长，有 $5\mathrm{s}$，所以考虑卡时（前面卡时部分放个 $4.8\mathrm{s}$ 比较合适，后面 $1000$ 组交互 $0.2\mathrm{s}$ 绰绰有余）：具体地，上面的字符串不止生成一组，一直随机若干组字符串，每次如果不同的 $f(w_i+w_j)$ 的数量比上一次多那么就继承当前次的答案；
- 这种做法看起来不错，但是会在 $n$ 不大不小（大约是 $[7,18]$ 这个范围）的时候出错：因为在这个时候字符串不长，可供询问的 $(i,j)$ 也不多，所以可能多重复几个 $f(w_i+w_j)$ 就寄了；考虑每一位 $\dfrac{1}{2}$ 概率为 $\texttt{O}$ 或 $\texttt{X}$ 生成的字符串有什么弊端——它的所有段内字符都相等的极长连续段不会太长，这样能产生的本质不同的子串个数必然也不是很多；于是我们将生成字符串的方式改一改——每次以 $p\left(p>\dfrac{1}{2}\right)$ 的概率将该位的字符设为和前一位相等的字符，$1-p$ 的概率设为和前一位不相等的，这样可以产生更多的本质不同的子串，经试验取 $p=\dfrac{3}{5}$ 可以通过此题。

自此我们用乱搞切掉了一道 $\color{Red}\mathrm{*2600}$。

代码里面的 AtCoder Library 部分请自行补全，或使用 AtCoder Custom Test 测试样例。

放代码（GNU C++17, with AtCoder Library）：

```cpp
#include<bits/stdc++.h>
#include<atcoder/string>
#define int long long
using namespace std;
mt19937 g(time(0));
int lst; inline bool get(){
  if(g()%5<=3)return lst;
  return lst=!lst;
} // 特殊的生成方式——3/5 的概率继承上一个
inline int f(string s){
  int n=s.length(),c=n*(n+1)>>1;
  for(int i:atcoder::lcp_array(s,atcoder::suffix_array(s)))c-=i;
  return c;
} // 计算本质不同的子串个数
main(){
  ios::sync_with_stdio(false);
  int n,bs=0,st=clock(); cin>>n;
  vector<string> v;
  map<int,pair<int,int> > mp;
  mt19937 g(time(0));
  uniform_int_distribution<> l(n*15,n*30);
  while(1.0*(clock()-st)/CLOCKS_PER_SEC<4.8){
    vector<string> a(n);
    for(int j=0;j<n;j++){
      int x=l(g);
      for(int k=0;k<x;k++)
        a[j]+=(get()?'X':'O');
    } // 随机生成字符串
    vector c(n,vector<int>(n));
    set<int> s;
    for(int i=0;i<n;i++)
      for(int j=0;j<n;j++)
        s.emplace(c[i][j]=f(a[i]+a[j]));
    // 计算种类数，如果种类数大于当前最优解就更新
    if(s.size()>bs){
      bs=s.size(),v=a;
      for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
          mp[c[i][j]]=make_pair(i+1,j+1);
    } // 打表
  } // 卡时进行贪心
  for(int i=0;i<n;i++){
    cout<<v[i];
    if(i<n-1)cout<<'\n';
    else cout<<endl;
  } // 给出方案
  int q; cin>>q;
  while(q--){
    int x; cin>>x;
    auto [a,b]=mp[x];
    cout<<a<<' '<<b<<endl;
  } // 回答询问
  return 0;
}
```

---

## 作者：shicj (赞：1)

Upd：可以使用 AtCoder Lib 打表，可以在几秒内得到结果，详见文章末尾。


**打表做法**（~可能~不太具有普遍性，但确实可以）~$114514$ 是一个很好的随机种子~。

首先，做一个非常简单的优化：为了使拼接后的子串种类不重复，可以构造使得其中一种符号远少于另一种，减少打表的次数（我的程序里控制比例为一比十）。

除此之外，其他所有内容都使用了暴力做法，求值函数为 $O(n^3)$，判断函数为 $O(n^2\log n)$（使用了 `map`），最终单次枚举时间复杂度约为 $O(n^5\log n)$，在机房的 `Intel(R) Core(TM) i5-6500 CPU @ 3.20GHz` 上花了几分钟时间。

这个算法中最重要的是选择正确的随机种子，在多次尝试后，我们发现将 $114514$ 作为 `mt19937` 的种子来运行只需要一次枚举即可得出答案！

这是打表程序：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n;
mt19937 Rand();
string random(int size){
	string s="";
	for(int i=1;i<=size;i++){
		if(Rand()%10){
			s+='X';
		}
		else{
			s+='O';
		}
	}
	return s;
}
int getVal(string s){
	int tot=0;
	map<string,int>mp;
	for(int i=0;i<s.size();i++){
		for(int j=1;j<=s.size()-i;j++){
			string ss=s.substr(i,j);
			mp[ss]=1;
		}
	}
	for(auto _:mp){
		tot++;
	}
	return tot;
}
int N=30,mxl=5,mnl=1;
string s[10001];
int ans[1001][1001];
void init(){
	for(int i=1;i<=N;i++){
		mxl=i*20-1;
		mnl=min(i,15)*20-2;
		s[i]=random(Rand()%(mxl-mnl+1)+mnl);
	}
}
bool check(){
	map<int,int>mp;
	for(int i=1;i<=N;i++){
		for(int j=1;j<=i;j++){
			cerr<<"#";
		}
		for(int j=i+1;j<=30;j++){
			cerr<<"-";
		}
		cerr<<endl;
		for(int j=1;j<=N;j++){
				if(mp[getVal(s[i]+s[j])]!=0){
					return 0;
				}
				else{
					mp[getVal(s[i]+s[j])]=1;
					ans[i][j]=getVal(s[i]+s[j]);
				}
		}
	}
	cerr<<endl;
	return true;
}
int main(){
	freopen("114514.txt","w",stdout);
	cerr<<"input the seed:"<<endl;
	int sd;
	//cin>>sd;
  sd=114514
	Rand.seed(sd);
	cerr<<"now use seed "<<sd<<endl;
	int tot=0;
	while(1){
		tot++;
		init();
		if(check()){
			cerr<<"#"<<tot<<" "<<"OK!"<<endl;
			cout<<"string s["<<N+10<<"]={\"\",";
			for(int i=1;i<=N;i++){
				cout<<"\""<<s[i]<<"\",";
			}
			cout<<"};";
			cout<<endl;
			for(int i=1;i<=N;i++){
				for(int j=1;j<=N;j++){
					cout<<"    ans["<<i<<"]"<<"["<<j<<"]="<<ans[i][j]<<";"<<endl;
				}
			}
			while(1);
			return 0;
		}
		else{
			cerr<<"#"<<tot<<" "<<"Fail!"<<endl;
		//	for(int i=1;i<=N;i++){
		//		cout<<s[i]<<" ";
		//	}
		//	cout<<endl;
		}
	}

	return 0;
}
```

运行情况：

![](https://cdn.luogu.com.cn/upload/image_hosting/ldwyxszl.png)

输出：

![](https://cdn.luogu.com.cn/upload/image_hosting/3gos503g.png)

最终代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
string s[40]={"","XXXXXOXXXXXXXOXXX  ......"};
int ans[40][40];
int main(){
  	ans[1][1]=414;
    ans[1][2]=1258;
    ......
    int n,k,q;
	cin>>n;
	for(int i=1;i<=n;i++){
		cout<<s[i]<<endl;
	}
	cin>>q;
	while(q--){
		cin>>k;
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				if(ans[i][j]==k){
					cout<<i<<" "<<j<<endl;
				}
			}
		}
	}
	return 0;
}
```
![](https://cdn.luogu.com.cn/upload/image_hosting/40hyjpf0.png)


**另：我们发现@徐振轩2011的 UID（1334925）也是一个很好的种子**

**AtCoder Lib 优化** 

```cpp
int getVal(string s){
    vector<int> sa = suffix_array(s);
    long long answer = 1LL * s.size() * (s.size() + 1) / 2;
    for (auto x : lcp_array(s, sa)) {
        answer -= x;
    }
	return answer;
}
```

---

## 作者：liangbowen (赞：1)

[blog](https://www.cnblogs.com/liangbowen/p/18513292)。一个简单很多的做法。

直接随机的话很难随出答案。但如果**钦定 `O` 的数量远大于 `X` 的数量**，本质不同子串数量就会与所有 `O` 的间隔位置相关，而这个的重复概率会低很多。

直接随机可以稳定在 $5$ 次以内找出合法解。提交打表程序即可通过。

[一个可能的实现](https://codeforces.com/contest/1970/submission/288680642)。（Generator 贺了一个 SA 科技）

---

