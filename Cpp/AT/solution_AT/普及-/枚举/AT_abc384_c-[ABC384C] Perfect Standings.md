# [ABC384C] Perfect Standings

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc384/tasks/abc384_c

高橋くんは、プログラミングコンテストを主催することにしました。

コンテストは A 問題、B 問題、C 問題、D 問題、E 問題の $ 5 $ 問からなり、それぞれの配点は $ a $ 点、$ b $ 点、$ c $ 点、$ d $ 点、$ e $ 点です。

コンテストには $ 31 $ 人が参加し、全員が $ 1 $ 問以上解きました。

より具体的には、文字列 `ABCDE` の空でない（連続するとは限らない）部分列すべてについて、その部分列を名前とする参加者が存在し、その参加者は名前に含まれる文字に対応する問題をすべて解き、それ以外の問題は解きませんでした。

例えば、A さんは A 問題のみを、BCE さんは B 問題、C 問題、E 問題を解きました。

参加者の名前を、取った点数が大きいほうから順に出力してください。 ただし、参加者が取った点数は、その参加者が解いた問題の配点の合計です。

ただし、同じ点数を獲得した参加者については、名前が辞書順で小さいほうを先に出力してください。

 辞書順で小さいとは？辞書順とは、一言で説明すると「単語が辞書に載っている順番」を意味します。

より厳密には、英大文字からなる相異なる文字列 $ S,T $ について、$ S $ が $ T $ より辞書順で小さいとは、以下の条件のどちらかが成り立つことを意味します。

- $ S $ の長さ $ |S| $ が $ T $ の長さより短く、$ T $ の先頭 $ |S| $ 文字が $ S $ と一致する
- ある整数 $ 1\leq\ i\leq\min\lbrace|S|,|T|\rbrace $ が存在して、次の $ 2 $ つの条件を両方を満たす
  - $ 1\leq\ j\lt\ i $ を満たすすべての整数 $ j $ に対して $ S $ の $ j $ 文字目と $ T $ の $ j $ 文字目が等しい
  - $ S $ の $ i $ 文字目が $ T $ の $ i $ 文字目よりアルファベット順で小さい
 
例えば、$ S= $ `AB` $ ,T= $ `ABC` とすると、ひとつめの条件が成り立つため $ S $ は $ T $ より小さいです。 また、$ S= $ `ABD` $ ,T= $ `ACD` とすると、ふたつめの条件が $ i=2 $ で成り立つため $ S $ は $ T $ より小さいです。

## 说明/提示

### 制約

- $ 100\leq\ a\leq\ b\leq\ c\leq\ d\leq\ e\leq\ 2718 $
- 入力はすべて整数
 
### Sample Explanation 1

それぞれの参加者の得点は以下のようになります。 !\[\](https://img.atcoder.jp/abc384/4dac80dfad9b0f66c75fec40eedb5e2d.png) 例えば、ADE さんと BCE さんは同じ得点を獲得していますが、ADE さんのほうが辞書順で小さい名前をもつため、ADE さんを先に出力してください。

## 样例 #1

### 输入

```
400 500 600 700 800```

### 输出

```
ABCDE
BCDE
ACDE
ABDE
ABCE
ABCD
CDE
BDE
ADE
BCE
ACE
BCD
ABE
ACD
ABD
ABC
DE
CE
BE
CD
AE
BD
AD
BC
AC
AB
E
D
C
B
A```

## 样例 #2

### 输入

```
800 800 900 900 1000```

### 输出

```
ABCDE
ACDE
BCDE
ABCE
ABDE
ABCD
CDE
ACE
ADE
BCE
BDE
ABE
ACD
BCD
ABC
ABD
CE
DE
AE
BE
CD
AC
AD
BC
BD
AB
E
C
D
A
B```

## 样例 #3

### 输入

```
128 256 512 1024 2048```

### 输出

```
ABCDE
BCDE
ACDE
CDE
ABDE
BDE
ADE
DE
ABCE
BCE
ACE
CE
ABE
BE
AE
E
ABCD
BCD
ACD
CD
ABD
BD
AD
D
ABC
BC
AC
C
AB
B
A```

# 题解

## 作者：违规用户名1053866 (赞：5)

把每个人的名字和做对的题放在结构体里，求出所有人的分数后，排个序即可。
```cpp
#include<bits/stdc++.h>
using namespace std;
int a,b,c,d,e;
struct node{
	string s;
	int score;
}st[105];
bool cmp(node a,node b){
	if(a.score!=b.score)
		return a.score>b.score;
	return a.s<b.s;
}
int main(){
	cin>>a>>b>>c>>d>>e;
	st[1].s="ABCDE";
	st[2].s="BCDE";
	st[3].s="ACDE";
	st[4].s="ABDE";
	st[5].s="ABCE";
	st[6].s="ABCD";
	st[7].s="CDE";
	st[8].s="BDE";
	st[9].s="ADE";
	st[10].s="BCE";
	st[11].s="ACE";
	st[12].s="BCD";
	st[13].s="ABE";
	st[14].s="ACD";
	st[15].s="ABD";
	st[16].s="ABC";
	st[17].s="DE";
	st[18].s="CE";
	st[19].s="BE";
	st[20].s="CD";
	st[21].s="AE";
	st[22].s="BD";
	st[23].s="AD";
	st[24].s="BC";
	st[25].s="AC";
	st[26].s="AB";
	st[27].s="E";
	st[28].s="D";
	st[29].s="C";
	st[30].s="B";
	st[31].s="A";
	st[1].score=a+b+c+d+e;
	st[2].score=b+c+d+e;
	st[3].score=a+c+d+e;
	st[4].score=a+b+d+e;
	st[5].score=a+b+c+e;
	st[6].score=a+b+c+d;
	st[7].score=c+d+e;
	st[8].score=b+d+e;
	st[9].score=a+d+e;
	st[10].score=b+c+e;
	st[11].score=a+c+e;
	st[12].score=b+c+d;
	st[13].score=a+b+e;
	st[14].score=a+c+d;
	st[15].score=a+b+d;
	st[16].score=a+b+c;
	st[17].score=d+e;
	st[18].score=c+e;
	st[19].score=b+e;
	st[20].score=c+d;
	st[21].score=a+e;
	st[22].score=b+d;
	st[23].score=a+d;
	st[24].score=b+c;
	st[25].score=a+c;
	st[26].score=a+b;
	st[27].score=e;
	st[28].score=d;
	st[29].score=c;
	st[30].score=b;
	st[31].score=a;
	sort(st+1,st+32,cmp);
	for(int i=1;i<=31;i++)
		cout<<st[i].s<<"\n";
}
```

---

## 作者：ryf2011 (赞：4)

# 题目思路
其实题目说的很清楚了，且五个题目的分数是逐渐递增（可能相等）的。

由于排名中人的名字和数量是不变的，所以我们可以借助结构体打表，存储所有人的名字，以及这个人对应的分数。

这时，如何对数据进行排序呢？

我们先考虑根据分数排序，如果分数相同，则根据字典序排序。排序完成后，按排序顺序直接输出名字即可。

# 代码
注：本代码仅供参考。

```cpp
#include<iostream>
#include<cstdio>
#include<string>
#include<cstring>
#include<algorithm>
using namespace std;
int a,b,c,d,e;
string names[]={"ABCDE","BCDE","ACDE","ABDE","ABCE","ABCD","CDE",
"BDE","ADE","BCE","ACE","BCD","ABE","ACD","ABD","ABC","DE","CE","BE",
"CD","AE","BD","AD","BC","AC","AB","E","D","C","B","A"}; //打表存储名字 
struct node{ //结构体存储信息 
	string name;
	int val;
} p[105];
bool cmp(node a,node b){ //cmp():告诉 sort() 排序方法 
	if(a.val!=b.val){ //先根据分数排序 
		return a.val>b.val;
	}
	if(a.val==b.val){ //后根据字典序排序 
		return a.name<b.name;
	}
}
int main(){
	scanf("%d %d %d %d %d",&a,&b,&c,&d,&e); //输入 
	for(int i=0;i<=30;i++){ //将数据计算并存入结构体 
		p[i+1].name=names[i];
		for(int j=0;j<names[i].size();j++){
			if(names[i][j]=='A'){
				p[i+1].val+=a;
			}
			else if(names[i][j]=='B'){
				p[i+1].val+=b;
			}
			else if(names[i][j]=='C'){
				p[i+1].val+=c;
			}
			else if(names[i][j]=='D'){
				p[i+1].val+=d;
			}
			else if(names[i][j]=='E'){
				p[i+1].val+=e;
			}
		}
	}
	sort(p+1,p+32,cmp); //排序 
	for(int i=1;i<=31;i++){ //输出 
		cout<<p[i].name<<'\n';
	}
	return 0;
}
```

#### 后记
更多内容，请移步至 [$\color{orange}\texttt{ryf2011}$](https://www.luogu.com.cn/user/1151973 "点我进入ryf2011")。

---

## 作者：4041nofoundGeoge (赞：2)

位运算的题目。

## 思路

一个大小为 $N$ 的集合 $S=\{s_0,s_1,\dots,s_{ N−1}\}$ 有 $2^N$ 个子集，可以按照以下方式对应到 $0$ 和 $2^{N−1}$ 之间的整数：

例如，$1$ 的二进制表示为 $00001$ ，因此它对应于 $\{A\}$；$10$ 的二进制表示为 $01010$ ，因此它对应于 $\{B,D\}$。看出来了吗？每一位上 $1$ 代表选他，$0$ 代表不选。

字典序的问题我们可以用 sort 排序即可。

## 代码

```cpp
#include <bits/stdc++.h>
using namespace std;

int main(){
    int a, b, c, d, e;
    cin >> a >> b >> c >> d >> e;
    map<int, vector<string>> scores;
    vector<string> p;
    for(int i = 1; i < (1<<5); ++i){
        string name = "";
        int score = 0;
        if(i & (1<<0)){ name += "A"; score += a; }
        if(i & (1<<1)){ name += "B"; score += b; }
        if(i & (1<<2)){ name += "C"; score += c; }
        if(i & (1<<3)){ name += "D"; score += d; }
        if(i & (1<<4)){ name += "E"; score += e; }
        p.push_back(name);
        scores[score].push_back(name);
    }
    for(auto &it : scores){
        sort(it.second.begin(), it.second.end());
    }
    for(int i = 2718*5; i >= 100; --i){
        if(scores.find(i) != scores.end()){
            for(auto name : scores[i]){
                cout << name << endl;
            }
        }
    }

    return 0;
}

```

---

## 作者：jinhangdong (赞：2)

我们枚举每道题目做没做对，然后计算出这个人有几分，并算做出题目的字典序，然后排序输出即可。


```cpp
#include<bits/stdc++.h>
using namespace std;
int a,b,c,d,e,cnt;
struct node
{
	int ans;
	string s; 
}o[10005];
bool cmp(node x,node y)
{
	if(x.ans==y.ans) return x.s<y.s;
	return x.ans>y.ans;
}
int main()
{
	cin>>a>>b>>c>>d>>e;
	for(int i=0;i<2;++i)//0表示这题每做对,1表示这题做对了。
	for(int j=0;j<2;++j)
	for(int k=0;k<2;++k)
	for(int r=0;r<2;++r)
	for(int t=0;t<2;++t)
	{
		cnt++;
		o[cnt].ans=i*a+j*b+k*c+r*d+t*e;
		if(i) o[cnt].s+='A';
		if(j) o[cnt].s+='B';
		if(k) o[cnt].s+='C';
		if(r) o[cnt].s+='D';
		if(t) o[cnt].s+='E';
	}
	sort(o+1,o+cnt+1,cmp);
	for(int i=1;i<=cnt;++i)
	{
		cout<<o[i].s<<"\n"; 
	}
	return 0;
}
```

---

## 作者：Happy_mouse (赞：0)

用了一种比较离谱的方法——写函数排序。

用二进制代表该个位置做出没有，$1$ 到 $31$ 就表示了所有人。写函数计算分数，不行比较字典序，排序即可。

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define ls u*2
#define rs u*2+1
#define fi first
#define se second
const int N=1e4+5;
int s[33],a[6];
char c[6]={' ','A','B','C','D','E'};
int js(int x){
	int sum=0;
	for(int i=1;i<=5;i++){
		sum+=a[i]*(x%2);
		x/=2;
	}
	return sum;
}//计算分值
string change(int x){
	string s="";
	for(int i=1;i<=5;i++){
		if(x%2) s+=c[i];
		x/=2;
	}
	return s;
}//转化成字符串
bool cmp(int x,int y){
	if(js(x)==js(y)) return change(x)<change(y);
	return js(x)>js(y);
}//排序
signed main(){
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	for(int i=1;i<=5;i++) cin>>a[i];//输入
	for(int i=1;i<=31;i++) s[i]=i;//给所有参赛者赋值
	sort(s+1,s+32,cmp);//排序
	for(int i=1;i<=31;i++){
		for(int j=1;j<=5;j++){
			if(s[i]%2) cout<<char(j+'A'-1);
			s[i]/=2;
		}
		cout<<'\n';
	}//输出
	return 0;
}
```

---

## 作者：Cosine_Func (赞：0)

简单的排序题。

显而易见的，通过的题目集合与输入无关，因此可以先打表存下通过的题目，再进行排序。排序函数要注意判字典序。

比较函数代码：
```cpp
bool cmp(string x,string y){
	int a=0,b=0;
	for(char i:x)a+=p[i-'A'];
	for(char i:y)b+=p[i-'A'];
	return a==b?x<y:a>b;
}
```
[参考代码](https://atcoder.jp/contests/abc384/submissions/60741575)

---

