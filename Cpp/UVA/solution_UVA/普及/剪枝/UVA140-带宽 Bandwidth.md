# 带宽 Bandwidth

## 题目描述

[problemUrl]: https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=3&page=show_problem&problem=76

[PDF](https://uva.onlinejudge.org/external/1/p140.pdf)

![](https://cdn.luogu.com.cn/upload/vjudge_pic/UVA140/c28a82a576401d68954e54e49ebe92f369cda3c9.png)

## 样例 #1

### 输入

```
A:FB;B:GC;D:GC;F:AGH;E:HD
#```

### 输出

```
A B C F G D H E -&gt; 3```

# 题解

## 作者：田字格 (赞：10)

## 分析与思路

说到排列，很容易想到枚举排列，将字母映射成id（数字），生成每种排列，分别计算带宽，取最小值。用两个vector存储相邻的节点，这样一来，这道题就很easy啦！！！

## 题解

```c++
#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
using namespace std;

const int maxn = 10;
int id[256], letter[maxn];

int main() {
  char input[1000];
  while(scanf("%s", input) == 1 && input[0] != '#') {
    // 计算结点个数并给字母编号
    int n = 0;
    for(char ch = 'A'; ch <= 'Z'; ch++)
      if(strchr(input, ch) != NULL) {
        id[ch] = n++;
        letter[id[ch]] = ch;
      }

    // 处理输入
    int len = strlen(input), p = 0, q = 0;
    vector<int> u, v;
    for(;;) {
      while(p < len && input[p] != ':') p++;
      if(p == len) break;
      while(q < len && input[q] != ';') q++;
      for(int i = p+1; i < q; i++) {
        u.push_back(id[input[p-1]]);
        v.push_back(id[input[i]]);
      }
      p++; q++;
    }

    // 枚举全排列
    int P[maxn], bestP[maxn], pos[maxn], ans = n;
    for(int i = 0; i < n; i++) P[i] = i;
    do {
      for(int i = 0; i < n; i++) pos[P[i]] = i; // 每个字母的位置
      int bandwidth = 0;
      for(int i = 0; i < u.size(); i++)
        bandwidth = max(bandwidth, abs(pos[u[i]] - pos[v[i]])); // 计算带宽
      if(bandwidth < ans) {
        ans = bandwidth;
        memcpy(bestP, P, sizeof(P));
      }
    } while(next_permutation(P, P+n)); //排列神器，要调用<algorithm>

    // 输出
    for(int i = 0; i < n; i++) printf("%c ", letter[bestP[i]]);
    printf("-> %d\n", ans);
  }
  return 0;
}
```

PS:参考刘汝佳程序

---

## 作者：Rbu_nas (赞：6)

首先当然感谢管理员的审核qwq

这道题呢因为文字翻译不太准确，本蒟奉上完整题意：

![](https://cdn.luogu.com.cn/upload/pic/32308.png)

![](https://cdn.luogu.com.cn/upload/pic/32292.png)

本题思维要求较高，另外刘汝佳和一些大牛的博客代码比较难懂、复杂，窝就来一发NOIp幼儿园组都能看懂的好了2333

这道题有很多难点，我会在重点处划标记哒qwq

---

0.**读入问题**
	
woc小蒟蒻看题意都看了半天，一看数据`A:FB;B:GC;D:GC;F:AGH;E:HD`

夹着手的烟微微发抖...

让我们理理思路，首先珂以看到每个点与多个点有**无向边**，两次标记不多说； 其次是如何读取到`:`与`;`
前后的点，这里用一个矩阵就可以存了（8个点）。

那我的思路是酱紫的：一次存一行后**用一个数来表示是否找到`:`前的字母，然后对`;`前的字母建边。**

还有一个坑就是可以观察到样例里的`C`这个点并没有建边，后面需要判断一下。

上代码和注释:

```cpp
	char s[100];
	scanf("%s",s);
	if (s[0]=='#')
		return false;
	memset(g,0,sizeof(g)); //存储边
	memset(id,0,sizeof(id)); //标记字母是否出现
    tot=0; //出现的字母总数
	int pre=-1; //`:`前的字母是否出现
	for (int i=0; s[i]; i++)
	{
		if (s[i]==':')
			pre=s[i-1]-'A'; //如果出现就赋值（即s[i-1]）
		else
		{
			if (s[i]==';') 
				pre=-1; //同时标记一下`;`
			if (pre!=-1) //如果这里改变了值，就说明找到了`:`前的点
			{
				g[pre][s[i]-'A']=true;
				g[s[i]-'A'][pre]=true; //建无向边
			}
		}
		if (s[i]>='A' && s[i]<='Z')
			id[s[i]-'A']=true; //对每一次出现的字母标记一下，因为最后输出按字典序，所以先按字典序排好
	}
```

那么到这里建边已经完成了，由于按字典序输出就把出现的点按字典序存在search数组里：

```cpp
for (int i=0; i<26; i++)
		if (id[i])
			search[tot++]=i; //tot记录出现字母的总数，然后按字典序存储
```

---
1.**主函数处理**

这部分主要就是思路问题，我们每次dfs出当前最大带宽，然后与最大带宽比较更新就好了，注意每次flag数组清空

```cpp
int main()
{
	while (init())
	{
		best_dist=26;
		memset(flag,0,sizeof(flag));
		dfs(0,0);
		for (int i=0; i<tot; i++)
			printf("%c ",best[i]+'A');
		printf("-> %d\n",best_dist);//按照格式输出
	}
	return 0;
}
```
---
2.**最优性剪枝dfs**

这可谓是整个代码的核心，其实并不难想，首先我们处理dfs到这一步时是否完成，然后对带宽进行更新，有更小的取更小的。很多人题意不太理解，其实就是**dfs出本次最大带宽，然后与目前最大带宽比较，选小者留下，就实现了最大带宽最小值**

先给出一段**判断是否完成**的伪代码qwq：

```cpp
void dfs(int step,int dist)//step表示步数，dist表示带宽
if (step==tot)//此时已经满足了要求，即与字母种数相同
{
	if (dist<best_dist)
	{
		for (int i=0; i<tot; i++)
			best[i]=ans[i];
		best_dist=dist;//此时更新掉最小带宽
	}
}
```
那么对于寻找部分，可以采用最优性剪枝，因为一旦找出dist>=best_dist，下一次就不用往下寻找了

那么这就是**代码核心**：

```cpp
for (int j=0; j<step; j++)
	if (g[ans[j]][search[i]])
	{
		if (step-j>=best_dist)
		{
			check_ok=false;//记录，表示下次不用往下寻找
			break;//直接brak
		}
		if (step-j>cur_max_dist)
			cur_max_dist=step-j;//更新一下这个点的dist
	}
```

那么根据题意，dfs很快就能出来辣

```cpp
void dfs(int step,int dist)
{
	if (step==tot)
	{
		if (dist<best_dist)
		{
			for (int i=0; i<tot; i++)
				best[i]=ans[i];
			best_dist=dist;
		}
	}
	else
	{
		for (int i=0; i<tot; i++)
		{
			if (!flag[search[i]])//还没有标记过这个字母
			{
				bool check_ok=true;//下次是否需要寻找
				int cur_max_dist=0;//当前点的dist
				for (int j=0; j<step; j++)
					if (g[ans[j]][search[i]])
					{
						if (step-j>=best_dist)
						{
							check_ok=false;
							break;
						}
						if (step-j>cur_max_dist)
							cur_max_dist=step-j;
					}
				if (check_ok)
				{
					flag[search[i]]=true;
					ans[step]=search[i];//记录ans数组
					dfs(step+1,max(dist,cur_max_dist));
					flag[search[i]]=false;//重新标记为false，warning：如果不标记代表着永远不能再碰到这个点
				}
			}
		}
	}
}
```
那么此时代码已经能愉快的实现啦！奉上AC代码（珂参考前文讲解食用）：

```cpp
#include <cstdio>
#include <cstring>
#define max(a,b) ((a)>(b)?(a):(b)) 
using namespace std;
bool g[30][30];
bool id[30];
int search[30];
int tot;
bool init()
{
	char s[100];
	scanf("%s",s);
	if (s[0]=='#')
		return false;
	memset(g,0,sizeof(g));
	memset(id,0,sizeof(id));
	tot=0;
	int pre=-1;
	for (int i=0; s[i]; i++)
	{
		if (s[i]==':')
			pre=s[i-1]-'A';
		else
		{
			if (s[i]==';')
				pre=-1;
			if ( pre!=-1)
			{
				g[pre][s[i]-'A']=true;
				g[s[i]-'A'][pre]=true;
			}
		}
		if (s[i]>='A' && s[i]<='Z')
			id[s[i]-'A']=true;
	}
	for (int i=0; i<26; i++)
		if (id[i])
			search[tot++]=i;
	return true;
}
int ans[26],best[26],best_dist;
bool flag[26];
void dfs(int step,int dist)
{
	if (step==tot)
	{
	 
		if (dist<best_dist)
		{
			for (int i=0; i<tot; i++)
				best[i]=ans[i];
			best_dist=dist;
		}
	}
	else
	{
		for (int i=0; i<tot; i++)
		{
			if (!flag[search[i]])
			{
				bool check_ok=true;
				int cur_max_dist=0;
				for (int j=0; j<step; j++)
					if (g[ans[j]][search[i]])
					{
						if (step-j>=best_dist)
						{
							check_ok=false;
							break;
						}
						if (step-j>cur_max_dist)
							cur_max_dist=step-j;
					}
				if (check_ok)
				{
					flag[search[i]]=true;
					ans[step]=search[i];
					dfs(step+1,max(dist,cur_max_dist));
					flag[search[i]]=false;
				}
			}
		}
	}
}
int main()
{
	while (init())
	{
		best_dist=26;
		memset(flag,0,sizeof(flag));
		dfs(0,0);
		for (int i=0; i<tot; i++)
			printf("%c ",best[i]+'A');
		printf("-> %d\n",best_dist);
	}
	return 0;
}
```

---

## 作者：Jorisy (赞：3)

我们在输入时用 $a_i$ 表示出现过的第 $i$ 小的字母，便可以解决输入的一些困难。

接下来，用 dfs 枚举全排列即可。令 $w$ 为带宽，则每次准备搜索时进行一次最优性剪枝：如果 $w$ 已经大于等于目前来看最小的带宽，则停止操作。

而计算带宽，遍历一遍图即可。

AC Code：
```cpp
#include<bits/stdc++.h>
using namespace std;

int n,m,a[505],b[305],c[305],maxs,ans[305],f[15],g[305][305];

int d(int x,int y)//计算带宽
{
	for(int i=1;i<x;i++)
	{
		if(g[a[c[i]]][a[y]]) return x-i;
	}
	return 0;
}

void dfs(int dep,int w)
{
	if(dep>m)
	{
		maxs=w;
		for(int i=1;i<dep;i++) ans[i]=c[i];//存入答案
		return;
	}
	for(int i=1;i<=m;i++)
	{
		if(f[i]) continue;
		w=max(w,d(dep,i));//直接计算
		if(w>=maxs) continue;//剪枝
		f[i]=1;
		c[dep]=i;
		dfs(dep+1,w);
		f[i]=0;
	}
}

int main()
{
	string s;
	cin>>s;
	while(s!="#")
	{
		s+=";";
		m=0;
		maxs=114514;
		memset(f,0,sizeof(f));
		memset(g,0,sizeof(g));//多测注意清空
		for(int i=0;i<s.size();i++)
		{
			char p=s[i];
			i+=2;
			while(s[i]!=';') a[++m]=s[i],g[s[i]][p]=g[p][s[i]]=1,i++;//存图
			a[++m]=p;
		}
		sort(a+1,a+m+1);
		m=unique(a+1,a+m+1)-a-1;
		dfs(1,0);
		for(int i=1;i<=m;i++) cout<<(char)a[ans[i]]<<' ';
		cout<<"-> "<<maxs<<endl;
		cin>>s;
	}
 	return 0;
}

```

---

## 作者：王轩逸 (赞：3)

```cpp
#include<iostream>
#include<string>
#include<sstream>
#include<cstring>
using namespace std;
/*
①按照字母序为字母编号，确保编号小的在前面。
②全排列回溯，过程中进行剪枝，如果搜索过程中 bandwidth 值已经超过已经搜出
来过的 bandwidth 则剪掉。
③剪枝函数只需要将第 cur 个元素和前面 cur-1 个已选元素判断是否相邻和
bandwidth 值即可。
*/
const int N=10;
int n,id['Z'+1],G[N][N];//为每个字母节点编个号。
int ans,seq[N],tmp[N];
bool used[N];
char u,v,letter[N];//letter[i]记录节点 i 的字母值
inline int dis(int cur,int nid){
	for(int i=1;i<cur;i++)
		if(G[tmp[i]][nid])
			return cur-i;
	return 0;
}
void dfs(int cur,int bw){
	if(cur>n){
		ans=bw;
		memcpy(seq,tmp,sizeof(seq));
		return;
	}//到达目的地。
	//1-n 的全排列
	for(int i=1;i<=n;i++)
		if(!used[i]){
			bw=max(bw,dis(cur,i));//计算当前的 bandwidth 值
			if(bw<ans){
				used[i]=true;
				tmp[cur]=i;
				dfs(cur+1,bw);
				used[i]=false;
			}
		}
}
int main(){
	string line,node;
	char u,v;
	while(cin>>line&&line!="#"){//读取一组数据
		//初始化
		n=0,ans=10;
		memset(G,0,sizeof(G));
		memset(id,0,sizeof(id));
		memset(used,0,sizeof(used));
		//预处理字母，进行编号
		for(char i='A';i<='Z';i++)
			if(line.find(i)!=-1){
				id[i]=++n;
				letter[n]=i;
			}
		for(int i=0;i<line.size();i++)
			if(line[i]==';') line[i]=' ';
		stringstream sin(line);
		while(sin>>node){
			node[node.find(':')]=' ';
			stringstream ss(node);
			ss>>u;
			while(ss>>v)
				G[id[u]][id[v]]=G[id[v]][id[u]]=1;
		}
		dfs(1,0);
		for(int i=1;i<=n;i++)
			cout<<letter[seq[i]]<<' ';
		cout<<"-> "<<ans<<endl; 
	}
	return 0;
}
```


---

## 作者：baiABC (赞：1)

## 分析：
其实图的带宽就是**每两个结点在排列中的最大距离**。

这道题只要枚举结点排列，记录图的带宽中最小的并输出即可。

- 枚举排列可以用 ```next_permutation()```，图用邻接表存储（毕竟结点数 $n\;{\leq}\;8$）。
- 计算图的带宽时，可以由大（带宽一定小于 $n$）到小枚举，直到发现有两个在排列中的距离等于的该数的结点在图中相邻，这个数就是带宽。

可以按紫书上说的剪枝，但是代码会复杂一些，何况此题暴力也跑得挺快（STL 大法好！！）。
## 代码：
注意下面代码中 STL 的使用，利用 ```unique``` 去重，获得了图中的结点。以及注意对读入的处理。
```cpp
#include <bits/stdc++.h>
using namespace std;
bool G[26][26];
char s[100];
int main()
{
   while(scanf("%s", s), s[0] != '#')
   {
      memset(&G[0][0], false, sizeof G);
      vector <char> v, ansv;
      int ans = 8;
      char *p = s;
      do {
         char x = *p++;
         while(*++p != ';' && *p) // C 字符串以 '\0' 结尾，值为假
         {
            G[x-'A'][*p-'A'] = G[*p-'A'][x-'A'] = true; // G 的下标范围是 0~25
            v.push_back(*p); // 加入结点
         }
         v.push_back(x);
      } while(*p++);
      sort(v.begin(), v.end());
      v.resize(unique(v.begin(), v.end())-v.begin()); // 排序去重获得结点最小排列
      do {
         for(int l = v.size()-1; l; --l)
            for(int i = 0; i+l < v.size(); ++i)
               if(G[v[i]-'A'][v[i+l]-'A'])
               {
                  if(l < ans)
                  {
                     ans = l;
                     ansv = v; // 记录答案
                  }
                  goto OUT; // 跳出循环
               }
         OUT:;
      } while(next_permutation(v.begin(), v.end())); // 枚举排列
      /** 输出 **/
      for(int i = 0; i < ansv.size(); ++i)
         cout << ansv[i] << ' ';
      cout << "-> " << ans << endl;
   }
   return 0;
}
```

---

## 作者：hicode_002 (赞：1)

Uva140
[]https://www.luogu.com.cn/problem/UVA140
这道题比困难的串输出上简单一点，但思路上复杂一点

这道题是最优解问题，但数据小且要打印方案，所以用搜索

由于要求的是排列，所以适合用 dfs 枚举排列

但这个题的建图比较复杂，因为用了字符串且不是每个节点都给出，但是只需要把每个冒号前面的节点向后面的节点连一条边，再从后面的节点向冒号前面节点连一条边

由于 dfs 枚举排列是按照从小到大顺序枚举的，所以按字典序
 dfs 中的阶段 cur，这里表示这个位置上该填的数

如果排列生成完成就可以更新最优解了，更新最优解用小于不用小于等于，因为相等时要字典序最小的即先搜到的，更新的时候除了更新带宽，还要更新答案数组

因为前面的排列带宽已经算好，而加上这个数后只改变了这个数相连的节点，所以只需要找这个数相连的节点的距离最大值和当前带宽比较即可求出此时带宽

然后枚举排列，如果当前填这个数合法就把这个数相连的节点找找是否在排列中，在的话求一下距离，然后找最大值，当这个最大值大于当前 ans 时因为原 $nowdk<ans$
                                                                                
所以当前最大值 $>ans>nowdk$
  
此时怎么枚举也不可能更优，可以跳过当前节点枚举下一个节点，但不能 return

求出现在 nowdk 后再和 ans 比较，若 $nowdk>ans$ 也应剪枝，跳过当前节点
  
这里不能用刘汝佳的优化，因为建图时有重边没有处理（ vector 边表 ）
  
```c++
#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
using namespace std;
vector<int>edge[28];
int a[9],ans=1e3,b[9],c[9],len,anslen;
inline void dfs(int cur,int nowdk){
	if(cur==len){
		if(nowdk<ans){
			ans=nowdk;
			for(int i=0;i<cur;++i){
				b[i]=a[i];
			}
			anslen=cur;
		}
		
		return;
	}
	for(int i=0;i<len;++i){
		int ok=1;
		for(int j=0;j<cur;++j){
			if(a[j]==c[i]){
				ok=0;
				break;
			}
		}
		if(ok){
			a[cur]=c[i];
			int lmmax=0;
			int lin=0;
			for(int j=0;j<edge[a[cur]].size();++j){
				int kl=edge[a[cur]][j],lk=-1;
				for(int kls=cur-1;kls>=0;--kls){
					if(a[kls]==kl){
						lk=kls;
						++lin;
						break;
					}
				}
				if(lk!=-1){
					if(cur-lk>lmmax)lmmax=cur-lk;
					if(lmmax>ans)break;//剪枝1
				}
//				if(edge[a[cur]].size() -lin>ans)break;不能用，因为有重边，实际没有填的节点要比这个数偏小，即使现在>ans也有可能实际小于ans，可能这个节点可以取 ，故不能剪枝
			}
//			if(edge[a[cur]].size() -li/n>ans)continue;
			if(lmmax>nowdk)nowdk=lmmax;
			if(nowdk>ans){//剪枝2
				continue;
				
			}
			dfs(cur+1,nowdk);
		}
		
	}
}
int main(){
	while(1){
		len=0;
		anslen=0;
		 ans=1e3;
		 for(int i=0;i<28;++i)//多组数据清空
		edge[i].clear();
		memset(a,0,sizeof a);
		memset(b,0,sizeof b);
		memset(c,0,sizeof c);
		string s;
		cin>>s;
//		fflush(stdout);
//		cout<<s<<endl;
		if(s=="#")break;
		string ss="";
		for(int i=0;i<s.size() ;++i){//处理字符串，按分号拆开字符串，每个字符串再连边
			if(s[i]==';'){
				int yuan=ss[0]-'A';
				for(int j=2;j<ss.size() ;++j){
					int mu=ss[j]-'A';
					edge[yuan].push_back(mu);
					edge[mu].push_back(yuan);
				}
				ss="";
			}else if(s[i]!=' '&&s[i]!='\n'){
				ss+=s[i];
				
			}
		}
		if(ss!=""){//注意该行最后一个节点输入没有分号，要单独处理
			int yuan=ss[0]-'A';
				for(int j=2;j<ss.size() ;++j){
					int mu=ss[j]-'A';
					edge[yuan].push_back(mu);
					edge[mu].push_back(yuan);
				}
				ss="";
		}
		int l=0;
		for(int i=0;i<28;++i){
			if(edge[i].size()>0){
				c[l++]=i;//计算排列的长度，因为题目上没有给出，c数组是原排列，是按顺序排好的
			} 
		}
		len=l;
		dfs(0,0);
		for(int i=0;i<anslen;++i){
			cout<<(char)(b[i]+'A')<<" ";
		}
		cout<<"-> "<<ans<<endl;//箭头前后有空格
//		cout<<<<ans<<endl;
	}
	return 0;
}
```
但奇怪的是
我把
```c++
if(nowdk>ans){//剪枝2
	continue;
	
}
```
改成
```c++
if(nowdk>ans){//剪枝2
	return；
	
}
```
依然是 ac 的，但是没有什么道理，我觉得如果当前填的这个节点使带宽更大并不代表其他节点也会使带宽更大，所以 return 可能会漏解，但是竟然  ac 了，希望大神解答这个问题，为什么改成 return 也 AC ？
  
谢谢


---

## 作者：R3gr3t (赞：1)

UVa140 Bandwidth

## 分析

题目要求：对于$8$个字母，找到一个排列，使最大带宽最小。

因为只有$8$个字母，想到全排列，复杂度$O(8!)$很低。

<algorithm>中，有next\_permutation这个函数，可以方便的调下一个排列。



我的代码中用到了

```cpp
next_permutation(++V.begin(), V.end());
```

是因为我的vector是从1下标开始的。



### 读入

给出的字符不是连续的，所以并不能一边读一边映射字符，我用到了一个vector<char>

来存读入字符串中出现的所有字符，用vis数组标记，最后将vector升序排序。

-------

然后我用到了两个map，一个是<char, int>，一个是<int, char>。用来映射字符与数字。



我把字符串用一个string读了进来，之后用stringstream读这个字符串。



在每一个全排列中维护一个类似前缀和的东西，~~我是这么理解的~~。

可以$O(1)$求出两个字母间的距离。

-----

STL比较多，所以时间比较慢，跑了30ms，**注意多组输入输出**。

```cpp
#include <iostream>
#include <algorithm>
#include <sstream>
#include <cstring>
#include <cstdio>
#include <vector>
#include <string>
#include <map>

bool vis[200];

std::vector<char> v; 
std::vector<int> To[10];
std::map<char, int> M;
std::map<int, char> reM;

inline int Abs(int x) { if (x >= 0) return x; return -x; }

int main() {
	std::string str;
	while (std::cin >> str) { 
		if (str[0] == '#') break;

		v.clear(), M.clear(), reM.clear();
		for (int i = 0; i < 10; i++) To[i].clear();
		memset(vis, false, sizeof(vis));

		int len = str.size();
		for (int i = 0; i < len; i++) {
			if (str[i] >= 'A' && str[i] <= 'Z' && !vis[str[i]]) {
				v.push_back(str[i]);
				vis[str[i]] = true;
			}
		}
		str[len] = ';';

		std::sort(v.begin(), v.end(), std::less<char>());
		int size = v.size();
		for (int i = 0; i < size; i++) {
			M[v[i]] = i + 1;
			reM[i + 1] = v[i];
		}

		char c, t;
		std::stringstream ss(str);
		while (ss >> c) {
			ss >> t;
			char p;
			while (ss >> p) {
				if (p == ';') break;

				To[M[c]].push_back(M[p]);
				To[M[p]].push_back(M[c]);
			}
		}

		std::vector<int> V(1);
		for (int i = 1; i <= size; i++) V.push_back(i);

		std::vector<int> ans;
		int Min = 0x7f7f7f7f;
		do {
			int dis[10]; memset(dis, 0, sizeof(dis));
			std::vector<int> temp(1);

			for (int i = 1; i <= size; i++) {
				dis[V[i]] = dis[V[i - 1]] + 1;
			}

			for (int i = 1; i <= size; i++) {
				int Max = -1, pos = -1;
				for (int j = 0; j < To[i].size(); j++) {
					Max = std::max(Abs(dis[To[i][j]] - dis[i]), Max);
				}
				temp.push_back(Max);
			}

			int tmp = *std::max_element(++temp.begin(), temp.end());
			if (tmp < Min) {
				Min = tmp;
				ans = V;
			}
		} while (std::next_permutation(++V.begin(), V.end()));

		for (int i = 1; i <= size; i++) {
			std::cout << reM[ans[i]] << " ";
		}
		std::cout << "-> ";
		printf("%d\n", Min);
	}
	
	return 0;
}
```




---

## 作者：I_AK_IOI_and_NOI (赞：1)

## 解题思路

题目没有对排列加以限制，所有排列都是合法的。

如果一张图有 8 个顶点，那么排列就有 $8! = 40320$ 个，

每个排列都需要去找出最大带宽。

如果输入包含大量的图，总操作数就会非常大，有超时的风险。

因此，需要添加条件来进行剪枝。

我们知道，按照定义，一个顶点 $v$ 的带宽是与 $v$ 相邻的顶点在顶点序列中与点 $v$ 的最长距离。

一个序列的带宽是这些距离的最大值。

那么，用一个变量 $bw$ 记录当前排列已经验证过的点的带宽，

$bwmin$ 代表已经找到的最小带宽。如果在验证过程中 $bw \ge bwmin$，

显然这个排列取到的带宽一定会大于 $bwmin$，

不可能是要求的最优解。那么我们可以直接放弃对这个排列继续验证。

通过 next_permutation 可以获得下一个排列（头文件 algorithm），

当一个序列已经达到最大排列，再调用此函数，

就会重新回到最小排列，并返回 false，

代表本次重排已经无法将排列变为更大的字典序。

用数组 $g$ 存储一个邻接矩阵代表一个图的每条边。

用数组 $a$ 代表 26 个大写字母在图中出现的情况。

$c$ 为顶点序列，当找到更小的解时，将这个序列抄送给 $d$，以备输出。

字母 A 的 ASCII 码是 65，存储和演算时我们用 0 ~ 25 分别代表 A 到 Z。

输出的时候，所有的值要加回 65 再打印到屏幕上。

algorithm 中的 find 函数可以以线性的复杂度来查找无序序列中的值。

当在序列中找到两个邻接点并计算了距离以后，

将这个计算结果取绝对值才能最终求得一点的带宽，

否则会出现负数，不符合要求。

## 三、AC 代码
```
#include<cstdio>
#include<cstdlib>
#include<algorithm>
#include<bitset>
using namespace std;
#pragma warning(disable:4996)
bitset<26> g[26], a; char t, u, v, c[9], d[9], * ptr, bwmin, bw, p, exitfor;
int main() {
	for (;;) {
		a.reset(); fill(c, c + 8, 0); bwmin = 127; p = 0; exitfor = 0;
		for (unsigned char i = 0; i < 26; ++i)g[i].reset();
		for (;;) {
			t = getchar();
			if (t == '#')return 0;
			else if (t == ':') {
				for (;;) {
					v = getchar();
					if (v == ';') { exitfor = 1; break; }
					else if (v == '\n') { exitfor = 2; break; }
					else { v -= 65; g[u][v] = true, g[v][u] = true; a[v] = true; }
				}
				if (exitfor == 2)break;
			}
			else { u = t - 65; a[u] = true; }
		}
		for (unsigned char i = 0; i < 26; ++i)if (a[i] == true) { c[p] = i; ++p; }
		for (;;) {
			bw = 0; exitfor = 0;
			for (unsigned char i = 0; i < p; ++i) {
				for (unsigned char j = 0; j < 26; ++j) {
					if (g[c[i]][j] == 1) {
						ptr = find(c, c + p, j); bw = max(bw, (char)abs(ptr - c - i)); if (bw >= bwmin) { exitfor = 1; break; }
					}
				}
				if (exitfor == 1)break;
			}
			if (bwmin > bw) { bwmin = bw; for (unsigned char i = 0; i < p; ++i)d[i] = c[i]; }
			if (next_permutation(c, c + p) == 0)break;
		}
		for (unsigned char i = 0; i < p; ++i)printf("%c ", d[i] + 65);
		printf("-> %hhd\n", bwmin);
	}
}
```

---

## 作者：洛桃 (赞：0)

虽然借鉴了刘汝佳大佬的思路，但是代码由本人实现，并且一遍过了，所以就来发一个题解。

### 思路

其实很简单，dfs直接爆搜，枚举每一种可能的排列，同时记录当前已经出现的带宽，如果已经大于等于已有的答案，就进行剪枝，简直不要太easy。

然而~~恶心的~~UVa总是会弄一些字符串来搞我们心态，字符串处理是必要的一步，想做UVa的题，不会从字符串中提取信息的话，可能就会比较苦。当然，多做一点UVa的题，你就会变得轻车熟路了。

先放代码
```cpp
		bool is=0;int cur;
		for(int i=0;i<l;i++)
		{
			if(!is)
			{
				if(s[i]>='A'&&s[i]<='Z')
				{
					cur=s[i]-'A';
					if(!ex[cur])
					{
						ex[cur]=1;
						you[n++]=cur;
					}
				}
				else is=1;
			}
			else
			{
				if(s[i]>='A'&&s[i]<='Z')
				{
					if(!ex[s[i]-'A'])
					{
						ex[s[i]-'A']=1;
						you[n++]=s[i]-'A';
					}
					G[cur][s[i]-'A']=G[s[i]-'A'][cur]=1;
				}
				else is=0;
			}
		}
```

首先看清楚题目，虽然节点最多只有8个，但是字母从A到Z都有可能出现，由于我是用数字代替字母，所以数组要开到26以上。~~当然随手开大就没烦恼了~~

you数组代表我们在排列中可以选的字母，即有的字母，ex数组记录之前这个字母有没有出现过，是第一次出现就标记一下，然后加入you数组。

范围很小，所以可以有邻接矩阵存边，用来判断两点是否相邻。

is用来判断在：前还是在：后，遇到：is变1，碰到；is又会变回0。

n就是节点个数，应该看得懂。

处理好字符串，我们就得到了一个代表可选字母的you数组，之后的所有代码都用不上字母，我们只要在最后输出时强制转换类型并加回‘A’就ok了。

好的，接下来就是代码的核心部分dfs了，请看
```cpp
void upd()
{
	for(int i=0;i<n;i++)shu[i]=ans[i+1];
}
void dfs(int cur,int kk)
{
	if(kk>=minn)return;
	//cout<<n;
	if(cur==n+1)
	{
		if(kk<minn)
		{
			minn=kk;
			upd();
		}
		return;
	}
	for(int i=0;i<n;i++)
	{
		if(!vis[you[i]])
		{
			vis[you[i]]=1;
			ans[cur]=you[i];
			for(int j=1;j<=cur-1;j++)
			for(int k=j+1;k<=cur;k++)
			{
				if(G[ans[j]][ans[k]])
				kk=max(kk,k-j);
			}
			//cout<<kk<<endl;
			dfs(cur+1,kk);
			vis[you[i]]=0;
		}
	}
}
```
cur是目前所在位置，kk是当前的带宽，minn就是已知的最小带宽，ans数组是用来临时存的，shu数组才是输出时要用的。~~别问我为什么~~

vis数组用来记录这个字母是否用过，枚举排列时套的那两个for循环是用来求目前的带宽的，是相邻的就更新。由于数据范围过小，所以完全不用担心三层循环会超时。

upd函数用来更新数组，+1是因为我主函数里dfs初始的cur是1，所以ans数组存的东西下标是从1开始的。

要讲的都讲完了，就看代码吧。
### 代码部分
```cpp
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<vector>
using namespace std;
int n,ans[590],minn,shu[99],z[47];
int you[9];
bool ex[50],vis[97],G[93][93];
string s;
void upd()
{
	for(int i=0;i<n;i++)shu[i]=ans[i+1];
}
void dfs(int cur,int kk)
{
	if(kk>=minn)return;
	//cout<<n;
	if(cur==n+1)
	{
		if(kk<minn)
		{
			minn=kk;
			upd();
		}
		return;
	}
	for(int i=0;i<n;i++)
	{
		if(!vis[you[i]])
		{
			vis[you[i]]=1;
			ans[cur]=you[i];
			for(int j=1;j<=cur-1;j++)
			for(int k=j+1;k<=cur;k++)
			{
				if(G[ans[j]][ans[k]])
				{kk=max(kk,k-j);z[ans[j]]++;}
			}
			//cout<<kk<<endl;
			dfs(cur+1,kk);
			vis[you[i]]=0;
		}
	}
}
int main()
{
	while(cin>>s)
	{
		memset(G,0,sizeof(G));
		minn=1e9;
		n=0;
		if(s[0]=='#')break;
		int l=s.size();
		memset(ex,0,sizeof(ex));
		bool is=0;int cur;
		for(int i=0;i<l;i++)
		{
			if(!is)
			{
				if(s[i]>='A'&&s[i]<='Z')
				{
					cur=s[i]-'A';
					if(!ex[cur])
					{
						ex[cur]=1;
						you[n++]=cur;
					}
				}
				else is=1;
			}
			else
			{
				if(s[i]>='A'&&s[i]<='Z')
				{
					if(!ex[s[i]-'A'])
					{
						ex[s[i]-'A']=1;
						you[n++]=s[i]-'A';
					}
					G[cur][s[i]-'A']=G[s[i]-'A'][cur]=1;
				}
				else is=0;
			}
		}
		sort(you,you+n);
		dfs(1,0);
		for(int i=0;i<n;i++)printf("%c ",'A'+shu[i]);
		printf("-> %d\n",minn);
	}
	return 0;
}
```
最后提一句，UVa这一次居然不卡格式了，感动呜呜呜。

---

## 作者：rojic12138 (赞：0)

用了一中午来写这个，思路是存图、存字母、对所有可能的排序做检查。

**注意输入中不一定含边的来回**，样例输入中有A-F F-A,却没有以C为起点的，所以作为out的字符也要判断是否在Map中出现，并一次性存两次：g[in - 'A'][out - 'A'] = 1;     g[out - 'A'][in - 'A'] = 1;

每次read()时记得初始化数值，不要忘了M.clear()

在比较不同字母排列时，如果bw相等，选字典序小的

**在读入table后一定要先sort**，才能让next_permutation完全排列字母串，否则从原来顺序开始改变，得不到想要的结果
```

#include<cstdio>
#include<iostream>
#include<map>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;
string s;
int g[27][27],num;//num是字母个数
int bw=114514;//bandwidth带宽
map<char, bool>M;
char table[26];//有哪些字母
char ans[26];

bool read() {//读一遍，存图
	bw = 114514;
	num = 0;
	M.clear();
	memset(table, 0, sizeof(table));
	memset(g, 0, sizeof(g));
	memset(ans, 0, sizeof(ans));
	cin >> s;
	if (s == "#")
		return 0;
	else {
		int len = s.length();
		char in, out,tmp;
		bool isin = 1;//判断接下来字母是输入还是输出
		for (int i = 0; i < len; i++) {
			tmp = s[i];
			if (tmp == ';')
				isin = 1;
			else if (tmp == ':')
				isin = 0;
			else {//是字母
				if (isin) {
					in = tmp;
					if (!M.count(in)) {
						table[num++] = in;
						M[in] = 1;
					}
				}
				else {
					out = tmp;
					if (!M.count(out)) {
						M[out] = 1;
						table[num++] = out;
					}
					g[in - 'A'][out - 'A'] = 1;//会做重复工作但问题不大
					g[out - 'A'][in - 'A'] = 1;
				}
			}
		}
	}
	return 1;
}
void check(char tab[]) {
	int newbw=0;
	for (int i = 0; i < num - 1; i++)
		for (int j = i + 1; j < num; j++)
			if (g[tab[i] - 'A'][table[j] - 'A']) {
				newbw = max(j - i,newbw);
				if (newbw > bw)
					return;
			}
	if (newbw == bw && ans[0] >= 'A') {//如果bw相等，选字典序小的
		for (int i = 0; i < num; i++) {
			if (ans[i] < tab[i])
				return;
			else if (ans[i] > tab[i])
				continue;
		}
	}
	for (int i = 0; i < num; i++)
		ans[i] = tab[i];
	bw = newbw;
}
int main()
{
	while (read()) {
		sort(table, table + num);//重点！先sort才能让next_permutation完全排列字母串
		do {
			check(table);
		} while (next_permutation(table, table + num));
		for (int i = 0; i < num; i++)
			cout << ans[i] << " ";
		cout<<"-> " << bw << endl;
	}
	return 0;
}

```


---

