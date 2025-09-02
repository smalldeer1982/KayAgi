# Harry Potter and the Sorting Hat

## 题目描述

如你们所知，霍格沃茨有四个学院：格兰芬多，赫奇帕奇，拉文克劳和斯莱特林。新生的分院由分院帽来完成。学生们按照字母表的顺序一个个被叫到众人面前，每一个都需要戴上分院帽，在思虑过后，分院帽会正式宣布学生们应当进入的学院。

分院帽将根据学生们的个性进行分院：勇敢无畏并因此而高尚者属于格兰芬多；正直忠诚、坚忍诚实者进入赫奇帕奇；睿智博学、聪明敏锐者投身拉文克劳；头脑精明但狡诈阴险之人也许会进斯莱特林。无论如何，一年级的新生赫敏·格兰杰非常关心即将到来的分院。她研究了所有有关于分院帽的著作，并得到了一个简单得多的结论。如果学生们有亲戚此前在霍格沃茨学习过，分院帽会把他们分入与亲戚相同的学院。而在其他情况下，比如有些学生的亲戚曾就读于不同的学院，或亲戚都是赫敏父母一样的麻瓜，分院帽将把学生分给那一刻拥有新生最少的学院。

赫敏已经询问过名单上在她前面的学生的亲戚情况。现在她和她的新朋友哈利波特以及罗恩韦斯莱希望知道分院帽将把赫敏分入哪个学院。

## 样例 #1

### 输入

```
11
G????SS???H
```

### 输出

```
Gryffindor
Ravenclaw
```

## 样例 #2

### 输入

```
2
H?
```

### 输出

```
Gryffindor
Ravenclaw
Slytherin
```

# 题解

## 作者：Dehydration (赞：1)

## 前言：

[最优解](https://www.luogu.com.cn/record/list?pid=CF65D&orderBy=1&status=&page=1)。

[problem](https://www.luogu.com.cn/problem/CF65D)。

## 思路：

一道典型的**记忆化**搜索题目，检索时会遇到这两种情况：

#### \#1： 此人已经知道分在哪里了。

这种情况十分简单，此院的人数加一即可。

```c++
   if(s[i]!='?'){//如果明确，人数++ 
        if(s[i]=='G')
        {
            a[0]++;
            dfs(i+1);
            a[0]--;     	
		}
        if(s[i]=='H')
        {
            a[1]++;
            dfs(i+1);
            a[1]--;
    	}
        if(s[i]=='R')
		{
            a[2]++;
            dfs(i+1);
            a[2]--;		
		} 
		if(s[i]=='S')
		{
            a[3]++;
            dfs(i+1);
            a[3]--;			
		}
    }
```

#### \#2： 此人还不直到分在哪里。

这种情况看人数最少的都要搜一遍，记得回溯。

```c++
   else{//不明确 
        int minnum=*min_element(a,a+4);
        for(int j=0;j<4;j++){
            if(a[j]==minnum){//minnum为最小人数值，前面求的
                a[j]++;
                dfs(i+1);
                a[j]--;//开始搜索下一个 
            }
        }
    }
```

## 代码：

```c++
//应该已经很明确了，不懂就看看我的代码把

#include<bits/stdc++.h>
using namespace std;
#define ll long long
int n;
char s[10005];
ll getID(int a[]){//简单，不做解释 
    ll res=0;
    for(int i=0;i<4;i++){
        res=res*10000+a[i];
    }
    return res;
}
int a[4],c[4];
set<ll> se;
int dfs(int i){//记忆化搜索 
    ll ID=getID(a);
    if(se.count(ID))
        return 0;//K,O
    else{//求minnum
        se.insert(ID);
        if(i==n){
            int minnum=*min_element(a,a+4);
            for(int j=0;j<4;j++){
                if(a[j]==minnum){
                    c[j]=1;
                }
            }
            return 0;
        }
    }

    if(s[i]!='?'){//如果明确，人数++ 
        if(s[i]=='G')
        {
            a[0]++;
            dfs(i+1);
            a[0]--;     	
		}
        if(s[i]=='H')
        {
            a[1]++;
            dfs(i+1);
            a[1]--;
    	}
        if(s[i]=='R')
		{
            a[2]++;
            dfs(i+1);
            a[2]--;		
		} 
		if(s[i]=='S')
		{
            a[3]++;
            dfs(i+1);
            a[3]--;			
		}
    }
    else{//不明确 
        int minnum=*min_element(a,a+4);
        for(int j=0;j<4;j++){
            if(a[j]==minnum){
                a[j]++;//人数+1
                dfs(i+1);//开始搜索下一个 
                a[j]--;//回溯
            }
        }
    }
}

int main(){
	ios::sync_with_stdio(false); //养成抢最有解的好习惯（（（
	cin.tie(0);
	cout.tie(0);
    cin>>n;
    cin>>s;
    dfs(0);//从头开始搜索
    if(c[0])puts("Gryffindor"); if(c[1])puts("Hufflepuff"); if(c[2])puts("Ravenclaw"); if(c[3])puts("Slytherin");
	return 0;
    
}
```

题外：我更喜欢格兰芬多（废话）。

---

## 作者：wind_whisper (赞：1)

## $\text{Description}$
有 $4$ 个变量 $G,R,S,H$，初始的值均为 $0$.  
给出一个长度为 $n$ 的字符串，从前往后进行以下过程：
1. 若为 `G,R,S,H` 四者之一，则给对应的变量加一. 
2. 否则（为 `?` ），就给四个变量中最小的加一，若有多个最小值，则给任意一个加一.  

求处理完整个字符串后，四个变量是否**有可能**成为（非严格）最小值.  
$n\le 10000$.  
## $\text{Solution}$
设计状态为 $(i,a,b,c,d)$ 表示进行到第 $i$ 个字符，四个变量分别为 $a,b,c,d$.    
注意到，由于每次都只有在对相同的最小值加一时才会导致状态的分裂，并且可能会在后面的问号时合并状态，所以对于同一个 $i$，状态数是收敛的.  
直接 dfs 暴搜加 hash 去重即可.  
## $\text{Code}$
```cpp
#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define double long double 
#define ull unsigned long long
#define debug(...) fprintf(stderr,__VA_ARGS__)
const int N=1e4+100;
const double eps=1e-12;
inline ll read(){
  ll x(0),f(1);char c=getchar();
  while(!isdigit(c)){if(c=='-')f=-1;c=getchar();}
  while(isdigit(c)){x=(x<<1)+(x<<3)+c-'0';c=getchar();}
  return x*f;
}

int n,m;
int x[N];
map<ll,bool>mp;
bool vis[5];
void dfs(int k,int a,int b,int c,int d){
  int mn=min(a,min(b,min(c,d)));
  if(k>n){
    if(a==mn) vis[1]=1;
    if(b==mn) vis[2]=1;
    if(c==mn) vis[3]=1;
    if(d==mn) vis[4]=1;
    return;
  }
  ll o=1ll*a*(n+1)*(n+1)*(n+1)+1ll*b*(n+1)*(n+1)+1ll*c*(n+1)+d;
  if(mp[o]) return;
  if(x[k]){
    if(x[k]==1) dfs(k+1,a+1,b,c,d);
    else if(x[k]==2) dfs(k+1,a,b+1,c,d);
    else if(x[k]==3) dfs(k+1,a,b,c+1,d);
    else if(x[k]==4) dfs(k+1,a,b,c,d+1);   
  }
  else{
    if(a==mn) dfs(k+1,a+1,b,c,d);
    if(b==mn) dfs(k+1,a,b+1,c,d);
    if(c==mn) dfs(k+1,a,b,c+1,d);
    if(d==mn) dfs(k+1,a,b,c,d+1);
  }
  mp[o]=1;
}
signed main(){
#ifndef ONLINE_JUDGE
  freopen("a.in","r",stdin);
  freopen("a.out","w",stdout);
#endif
  n=read();
  char c;
  for(int i=1;i<=n;i++){
    scanf(" %c",&c);
    if(c=='G') x[i]=1;
    else if(c=='H') x[i]=2;
    else if(c=='R') x[i]=3;
    else if(c=='S') x[i]=4;
  }
  dfs(1,0,0,0,0);
  if(vis[1]) printf("Gryffindor\n");
  if(vis[2]) printf("Hufflepuff\n");
  if(vis[3]) printf("Ravenclaw\n");
  if(vis[4]) printf("Slytherin\n");
}
/*
*/

```



---

## 作者：Huangjy88 (赞：0)

# CF65D题解
## 思路分析
一道**记搜**的题目。

如果直接暴力搜索，时空复杂度会爆炸，考虑**记忆化**。但状态怎么记录呢？可以用**哈希**。
## 具体实现
用数组记录每个学院的人数（可以直接用字符的码值），每次深搜到的状态可以用 `STL::set` 来记录，判重。深搜到底时，循环找出最小值并记录即可。

`Tips`：要开 `long long`，还有输出的顺序

其他细节在代码里：
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=1e4;
int n;
string s,t="GHRS";
int a[130];
set<int>se;
bool vis[130];
int get_hash(){//哈希
    int m=0;
    for(int i=0;i<4;i++) m=m*N+a[t[i]];
    return m;
}
void dfs(int step){
    if(step==n){//边界
    int minn=a[t[0]];
	for(int i=1;i<4;i++) minn=min(a[t[i]],minn);
	for(int i=0;i<4;i++){
	    if(a[t[i]]==minn){
		vis[t[i]]=1;//标记
	    }
	}
	return;
    }
    if(s[step]!='?'){//学院确定
	a[s[step]]++;
	int k=get_hash();
	if(!se.count(k)){
	    se.insert(k);
	    dfs(step+1);
	}
	a[s[step]]--;
    }
    else{//学院不确定
	int minn=a[t[0]];
	for(int i=1;i<4;i++) minn=min(a[t[i]],minn);
	for(int i=0;i<4;i++){
	    if(a[t[i]]==minn){
		a[t[i]]++;
		int k=get_hash();
		if(!se.count(k)){
		    se.insert(k);
		    dfs(step+1);
		}
		a[t[i]]--;
	    }
	}
    }
}
signed main(){
    cin>>n>>s;
    dfs(0);//深搜
    if(vis['G']) printf("Gryffindor\n");
    if(vis['H']) printf("Hufflepuff\n");
    if(vis['R']) printf("Ravenclaw\n");
    if(vis['S']) printf("Slytherin\n");//输出注意顺序
    return 0;
}

```

---

## 作者：NOOB_PRO (赞：0)

考试考了，看到没题解，~~想水一手我的玄学做法。。。~~由于太菜而不会效率更高的算法。
做法很简单，先给四个排重要度（在有多个最小值时，优先选重要度最大的）
但是单单是这样会挂，所以又用随机数来在多个最小值里选，就A了
```
#include<bits/stdc++.h>
using namespace std;
#define re read()
#define ri register int
inline int read(){
	int res=0,w=1;
	char ch=getchar();
	while(ch<'0'||ch>'9')
		ch=='-'?w=-1,ch=getchar():ch=getchar();
	while(ch>='0'&&ch<='9'){
		res=res*10+ch-'0';
		ch=getchar();
	}
	return w*res;
}
const int N=10;
int id[N],score[N];//GHRS
int T,n,flag[N];
char s[20005];
set<int>minpos;
void check(int op){
	for(ri i=1;i<=4;++i)
		score[i]=0;
	for(ri i=1;i<=n;++i){
		if(s[i]=='G')		++score[1];
		else if(s[i]=='H')	++score[2];
		else if(s[i]=='R')	++score[3];
		else if(s[i]=='S')	++score[4];
		else{
			int minn=0x3f3f3f3f;
			minpos.clear();
			for(ri j=1;j<=4;++j){
				if(score[j]<minn){
					minpos.clear();
					minpos.insert(j);
					minn=score[j];
				} else if(score[j]==minn)
					minpos.insert(j);
			}
			if(!op){
				for(ri j=1;j<=4;++j)
					if(minpos.count(id[j])){
						++score[id[j]];
						break;
					}	
			}
			else{
				while(1){
					int t=rand()%4+1;
					if(minpos.count(t)){
						++score[t];
						break;
					}
				}
			}
		}
	}
	int minn=0x3f3f3f3f,tot,now[N];
	for(ri i=1;i<=4;++i){
		if(score[i]<minn){
			tot=0;
			now[++tot]=i;
			minn=score[i];
		}else if(score[i]==minn)
			now[++tot]=i;
	}
	for(ri i=1;i<=tot;++i)
		flag[now[i]]=1;
}
int main(){
//	freopen("fighting.in","r",stdin);
//	freopen("fighting.out","w",stdout);
//	T=re;
	srand(time(0));
	n=re;
	scanf("%s",s+1);
	memset(flag,0,sizeof(flag));
	for(ri i=1;i<=4;++i)
		id[i]=i;
	check(0);
	while(next_permutation(id+1,id+4+1))
		check(0);
	for(ri i=1;i<=300;++i)
		check(1);
	if(flag[1])	printf("Gryffindor\n");
	if(flag[2])	printf("Hufflepuff\n");
	if(flag[3])	printf("Ravenclaw\n");
	if(flag[4])	printf("Slytherin\n");
	return 0;
}
```


---

