# [USACO17OPEN] Bovine Genomics S

## 题目描述

Farmer John 拥有 $N$ 头有斑点的牛和 $N$ 头没有斑点的牛。他刚刚完成了一门关于牛遗传学的课程，并确信他牛身上的斑点是由牛基因组中的突变引起的。

Farmer John 花费巨资对他的牛进行了基因组测序。每个基因组是一个由字符 A、C、G 和 T 组成的长度为 $M$ 的字符串。当他将牛的基因组排列起来时，会得到如下表格，这里展示的是 $N=3$ 的情况：

```
位置：1 2 3 4 5 6 7 ... M

斑点牛 1：A A T C C C A ... T  
斑点牛 2：G A T T G C A ... A  
斑点牛 3：G G T C G C A ... A  

普通牛 1：A C T C C C A ... G  
普通牛 2：A G T T G C A ... T  
普通牛 3：A G T T C C A ... T 
```

仔细观察这个表格后，他推测位置 2 和 4 足以解释斑点现象。也就是说，通过仅查看这两个位置的字符，Farmer John 可以预测哪些牛是有斑点的，哪些是没有斑点的（例如，如果他看到 G 和 C，这头牛一定是有斑点的）。

Farmer John 确信，斑点现象不仅仅可以通过基因组中的一个或两个位置来解释，而是可以通过查看三个不同的位置来解释。请帮助他计算能够解释斑点现象的三个不同位置集合的数量。

## 样例 #1

### 输入

```
3 8
AATCCCAT
GATTGCAA
GGTCGCAA
ACTCCCAG
ACTCGCAT
ACTTCCAT```

### 输出

```
22```

# 题解

## 作者：YBaggio (赞：14)

# 题意
$\verb!FJ!$ 有 $n$ 头有斑点和 $n$ 头没有斑点的牛。

他认为一头牛有没有斑点和它的基因有关，所以他获取了所有奶牛的基因。

这些基因以字符串的形式给出，字符串中只包含  $\verb!A,C,G,T!$。

如果 $\verb!FJ!$ 认为一头奶牛的基因的第 $i,j,k$ 个字符决定它有没有斑点，那么 $i,j,k$ 必须满足:

任意一头 **有斑点的** 牛的基因的第 $i,j,k$ 个字符没有一个**有斑点的** 牛与其重复。

求共有的多少个 **符合规定** 的 $i,j,k$。

### 举个例子1

**斑点牛** :

1. $\verb!ATG...!$           

2. $\verb!ACG...!$

3. $\verb!AGT...!$

**无斑牛** :

1. $\verb!ACC...!$

2. $\verb!ACC...!$

3. $\verb!ACC...!$

可见 $1,2,3$ 号位可以判断牛有没有斑点，因为没有一头斑点牛的 $1,2,3$ 号基因在无斑牛中出现过。

-----------

### 举个例子2

**斑点牛** ：

1. $\verb!ATG...!$；            

2. $\verb!ACC...!$；

3. $\verb!AGT...!$；

**无斑牛** ：

1. $\verb!ACC...!$；

2. $\verb!ACC...!$；

3. $\verb!ACC...!$；

可见 $1,2,3$ 号位不可以判断牛有没有斑点，因为有第 $2$ 头斑点牛的 $1,2,3$ 号基因在无斑牛中出现过。

## 思路

可以先从时间复杂度入手。


首先花 $O(m^3)$ 暴力枚举这三个位置，接下来的问题是如何在 $O(n)$ 的时间内判断。

可以先想想如何用 $O(n^2)$ 的时间判断。

对于多个字符串是否相同的判断，我们很容易想到哈希表。

先计算出每个斑点牛这三个位置的哈希值，再计算每个无斑牛的哈希值，看有没有相同的。

### **怎么优化呢？**

我么可以定义两个哈希数组: `hashs,hashp` ，分别储存斑点牛和无斑牛。设  `H` 一个为有斑牛的哈希值。那么我们将 $hashs_H$ 设为 `true`。
设 `h` 为一个无斑牛的哈希值。则将 $hashp_i$ 设为 `h`。

那么我们如果想要判断第 $i$ 个无斑牛的哈希值是否在斑点牛中出现过。就可以使用表达式 $hashs_{hashp_i}$ 来判断。

最后贴上代码：

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,ans;
char S[510][55],P[510][55];
int HashS[20000],HashP[20000];
bool B[55][55][55];
void hashS(int fir,int sec,int thi){
    memset(HashS,0,sizeof(HashS));
    for(int i=1;i<=n;i++){
        int tmp=(S[i][fir]-'A'+1)+(S[i][sec]-'A'+1)*26+(S[i][thi]-'A'+1)*26*26;
        HashS[tmp]=1;
    }
    return;
}
void hashP(int fir,int sec,int thi){
    memset(HashP,0,sizeof(HashP));
    for(int i=1;i<=n;i++){
        int tmp=(P[i][fir]-'A'+1)+(P[i][sec]-'A'+1)*26+(P[i][thi]-'A'+1)*26*26;
        HashP[i]=tmp;
    }
    return;
}
int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)cin>>S[i][j];
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++)cin>>P[i][j];
    }
    int fir,sec,thi;
    for(fir=1;fir<=m;fir++){
        for(sec=fir+1;sec<=m;sec++){
            for(thi=sec+1;thi<=m;thi++){
                bool flag=0;
                hashS(fir,sec,thi);
                hashP(fir,sec,thi);
                for(int i=1;i<=n;i++){
                    if(HashS[HashP[i]]){flag=1;break;}//哈希小技巧
                }
                if(flag)continue;
                B[fir][sec][thi]=1;//记录答案
            }
        }
    }
    for(int i=1;i<=m;i++){//统计答案
        for(int j=1;j<=m;j++){
            for(int k=1;k<=m;k++){
                if(B[i][j][k])ans++;
            }
        }
    }   
    printf("%d",ans);
    return 0;
}
```







---

## 作者：Lolierl (赞：8)

看见这题还没人发题解，赶紧来水一水~

其实这道题很简单，简单的小学生打钩反而比哈希更高效。

以下是代码：


    
    
    
    
            
```cpp
#include<iostream>
#include<cstring>
using namespace std;
int get(char x)
{
    if(x=='A')return 1;
    if(x=='C')return 2;
    if(x=='G')return 3;    //用类似离散化的方式打钩
    if(x=='T')return 4;
}
int main()
{
    int n,m;
    cin>>n>>m;
    int a[n+1][m],b[n+1][m];
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
        {
            char x;
            cin>>x;
            a[i][j]=get(x);   //读入处理
        }
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            {
                char x;
                cin>>x;
                b[i][j]=get(x);
            }
    int t[5][5][5];   //三维数组，虽然很耗空间好在这题数据小，程序简单
    int ans=0;
    for(int i=1;i<=m-2;i++)
        for(int j=i+1;j<=m-1;j++)
            for(int k=j+1;k<=m;k++)       //循环优化，不然很有可能丢分
            {
                bool f=true;
                memset(t,0,sizeof(t));
                for(int x1=1;x1<=n;x1++)
                    t[a[x1][i]][a[x1][j]][a[x1][k]]=1;     //打钩
                for(int x2=1;x2<=n;x2++)
                    if(t[b[x2][i]][b[x2][j]][b[x2][k]]){f=false;break;}     //如果已经出现，说明不符合要求，否则ans++。
                if(f)ans++;
            }
    cout<<ans;
    return 0;
}
```

---

## 作者：foryou_ (赞：5)

## 题意

给定 $2$ 组字符串，每组 $n$ 个，每个字符串包含 $m$ 个字符。

我们称一个三元组 $(i,j,k)$ 是合法的，当且仅当第二组的每个字符串中下标为 $(i,j,k)$ 的字符拼成的字符串与第一组的每个字符串中下标为 $(i,j,k)$ 的字符拼成的字符串均不相等。

现在需要你对于给定的 $2$ 组字符串，找出所有合法的三元组 $(i,j,k)$ 的数量。

## 分析

因为观察到题目中 $n,m$ 的数据范围都很小，所以我们考虑直接朴素枚举三元组 $(i,j,k)$，再依次检查合法性。

在检查三元组 $(i,j,k)$ 的合法性时，我们可以建立一个标记数组 $vis$：

- 首先遍历第一组字符串，对于第 $x$ 个字符串 $s_x$，将 $vis_{s_{x,i},s_{x,j},s_{x,k}}$ 标记为 $1$。

- 再遍历第二组字符串，对于第 $x$ 个字符串 $s_x$，若 $vis_{s_{x,i},s_{x,j},s_{x,k}}=1$（已被标记），则直接继续枚举下一个三元组。

- 否则，若第二组字符串遍历完成后仍没有被标记过的，将答案累加。

需要注意的细节是，我们可以将字符串中包含的 `A`、`C`、`G`、`T` 字母映射为 $0$、$1$、$2$、$3$ 四个数字，从而将字符矩阵转换为整数矩阵，方便存储。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;

int n,m,ans,num[31]; //num表示映射数组
int a[531][131],b[531][131]; //a,b是由字符矩阵转换为的整数矩阵
bool vis[31][31][31]; //vis是标记数组 


bool check(int x,int y,int z){ //检查三元组(x,y,z)是否合法 
	memset(vis,0,sizeof(vis)); //注意清空 
	for(int i=1;i<=n;i++)
	    vis[a[i][x]][a[i][y]][a[i][z]]=1; //标记
	for(int i=1;i<=n;i++)
	    if(vis[b[i][x]][b[i][y]][b[i][z]]) //被标记过了
	        return 0;
	return 1; 
}

int main(){
	cin>>n>>m;
	num['A']=0,num['C']=1,num['G']=2,num['T']=3; //映射字母
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++){
		    char c; cin>>c; a[i][j]=num[c]; //转为整数矩阵
		}
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++){
		    char c; cin>>c; b[i][j]=num[c]; //同上
		}
	for(int i=1;i<=m;i++) //枚举三元组 
		for(int j=i+1;j<=m;j++)
			for(int k=j+1;k<=m;k++)
				if(check(i,j,k)) ans++; //若合法则累加 
	cout<<ans;
	return 0;
}
```

---

## 作者：45dino (赞：3)

一道比较简单的题。

枚举三个点，用map存可能斑点牛的基因段，再和空白牛进行比较，如果全部不相同答案加1。

问题来了，如何比较简单地存储这个三个字符的基因段？

（仅供参考）：可以把ACGT分别当作1234，如果是处在第 $i$ 位，第 $l$ 位，第 $j$ 位的就是$a_i\times 10+a_l\times 10+a_j$。

举个例子，比如基因段AATCCCAT（11422214）的第2位（1），第3位（4），第5位（2）所组成的基因段就是142。

问题便迎刃而解，但写出来后竟玄学TLE了两个点，于是改用scanf，有吸了口氧……~~这酸爽~~然后就卡过去了。

喜闻乐见的代码：

```
#include<bits/stdc++.h>
using namespace std;
struct node{
	int x,y,z;
};
map<int,int> vis;
int n,m,dot[501][51],whi[501][51],ans;
int main()
{
	scanf("%d %d",&n,&m);
	for(int i=1;i<=n;i++)
	{
		string s;
		cin>>s;
		for(int l=0;l<s.size();l++)
		{
			if(s[l]=='A')
				dot[i][l+1]=1;
			if(s[l]=='C')
				dot[i][l+1]=2;
			if(s[l]=='G')
				dot[i][l+1]=3;
			if(s[l]=='T')
				dot[i][l+1]=4;
		}
	}
	for(int i=1;i<=n;i++)
	{
		string s;
		cin>>s;
		for(int l=0;l<s.size();l++)
		{
			if(s[l]=='A')
				whi[i][l+1]=1;
			if(s[l]=='C')
				whi[i][l+1]=2;
			if(s[l]=='G')
				whi[i][l+1]=3;
			if(s[l]=='T')
				whi[i][l+1]=4;
		}
	}
	for(int i=1;i<=m-2;i++)
		for(int l=i+1;l<=m-1;l++)
			for(int j=l+1;j<=m;j++)
			{
				vis.clear();
				bool flag=0;
				for(int k=1;k<=n;k++)
					vis[dot[k][i]*100+dot[k][l]*10+dot[k][j]]=1;
				for(int k=1;k<=n;k++)
					if(vis[whi[k][i]*100+whi[k][l]*10+whi[k][j]])
					{
						flag=1;
						break;
					}
				if(!flag)
					ans++;
			}
	cout<<ans;
	return 0;
}
```


---

## 作者：寒鸽儿 (赞：3)

### 这是一个来自蒟蒻的题解
    首先，这道题的题意是从所有基因组中找到三个位置，使得所有斑点牛在这三个位置的基因组与所有非斑点牛的基因组各不相同。
    那么最关键的问题是，如何不重不漏地枚举所有组合，以及如何判断是都有基因组重复。
    第一个问题，我们可以用递归实现组合型枚举来完成，这个模板还是比较经典的，详见代码calc()函数部分。
    第二个问题，我们可以用三维数组来表示所有出现过的情况(代码中的check()部分),记录所有斑点牛的情况，对于所有非斑点牛，检查是否重复即可。
    最后附上代码:
```cpp
#include <cstdio>

using namespace std;

int read(){											//菜爆的简单快读
	int x = 0,f = 1;
	char ch = getchar();
	while(ch < '0' || ch > '9'){if(ch == '-') f = -1; ch = getchar();}
	while(ch >= '0' && ch <= '9'){x = x * 10 + ch - '0';ch = getchar();}
	return x * f;
}

int cread(){											//字母不好记录空间，改为数字来存
	loop:
		char ch = getchar();
		if(ch == 'A') return 0;
		else if(ch == 'C') return 1;
		else if(ch == 'T') return 2;
		else if(ch == 'G') return 3;
		else goto loop;
}

int n,m;
int cnt = 0,ched[3];
int a[500][50];
int b[500][50];

bool check(){
	bool flag = true;
	int happen[4][4][4] = {0};							//先记录下来，再判重
	for(int i = 0;i < n;i++)
		happen[a[i][ched[0]]][a[i][ched[1]]][a[i][ched[2]]] = 1;
	for(int i = 0;i < n;i++)
		if(happen[b[i][ched[0]]][b[i][ched[1]]][b[i][ched[2]]] == 1){
			flag = false;
			break;
		}
	return flag;
}

void calc(int no,int cho){								//递归实现组合型排列
	if(cho == 3){
		if(check())
			cnt++;
		return;
	}
	if(no == m+1) return;
	calc(no+1,cho);
	ched[cho] = no;
	calc(no+1,cho+1);
}

int main(){
	n = read(),m = read();
	for(int i = 0;i < n;i++)
		for(int j = 1;j <= m;j++)
			a[i][j] = cread();
	for(int i = 0;i < n;i++)
		for(int j = 1;j <= m;j++)
			b[i][j] = cread();
	calc(1,0);
	printf("%d\n",cnt);
 	return 0;
}

```

---

## 作者：PragmaGCC (赞：3)

## 题目大意

给定两组字符串，要求出有多少个三元组 $(i,j,k)$ 使得两组中的字符串在这三个位置上没有完全相同的（组内不算）。

## 做法

发现数据范围很小，直接暴力。

三层循环枚举 $(i,j,k)$，然后判断是否合法，注意到只要有相同就不合法，可以直接开桶记录，而不是两层循环嵌套枚举（那样也不能保证本质不同）。

```cpp
#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;
const int N = 505, M = 55;
char a[2][N][M];
int n, m, ans;
int calc(char ch) {
    if (ch == 'A') return 1;
    else if (ch == 'C') return 2;
    else if (ch == 'G') return 3;
    else return 4;
}
int cnt[5][5][5];
int main(void) {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) scanf("%s", a[0][i] + 1);
    for (int i = 1; i <= n; i++) scanf("%s", a[1][i] + 1);
    for (int i = 1; i <= m; i++)
        for (int j = i + 1; j <= m; j++)
            for (int k = j + 1, flg = 1; k <= m; k++, flg = 1) {
                memset(cnt, 0, sizeof(cnt));
                for (int x = 1, u, v, w; x <= n; x++) {
                    u = calc(a[0][x][i]), v = calc(a[0][x][j]), w = calc(a[0][x][k]);
                    cnt[u][v][w] = 1;
                }
                for (int x = 1, u, v, w; x <= n; x++) {
                    u = calc(a[1][x][i]), v = calc(a[1][x][j]), w = calc(a[1][x][k]);
                    if (cnt[u][v][w]) { flg = 0; break; }
                }
                ans += flg;
            }
    printf("%d\n", ans);
    return 0;
}
```

---

## 作者：lmy_2011 (赞：1)

## 思路
1. 本题的重点是 $m$ ，而 $m$ 的数据很小，所以我们可以用时间复杂度为 $O(m^3)$ 的三重循环穷举来做。
2. 再用一个函数判断一直有斑点的狗是否满足要求。

之后我们就可以上代码了(更多细节请看注释)：
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,a[505][55],b[505][55],num[5],ans;//num用来将"A" "C" "G" "T"转化成1，2，3，4四个数字
bool vis[5][5][5];//用一个vis数组标记
bool check(int x,int y,int z){
	memset(vis,0,sizeof(vis));//注意每次询问都得清零
	for(int i=1;i<=n;i++)
		vis[a[i][x]][a[i][y]][a[i][z]]=true;//标记有斑点的
	for(int i=1;i<=n;i++)
		if(vis[b[i][x]][b[i][y]][b[i][z]])//检查无斑点的
			return false;
	return true;
}
int main(){
	cin>>n>>m;
	num['A']=1;//都转化成数字
	num['C']=2;
	num['G']=3;
	num['T']=4;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++){
			char x;//这样更省复杂度
			cin>>x;
			a[i][j]=num[x];//将他转换后存入数组
		}
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++){
			char x;
			cin>>x;
			b[i][j]=num[x];//同理
		}
	for(int i=1;i<=m;i++)
		for(int j=i+1;j<=m;j++)//注意从j+1开始，穷举需要不重不漏
			for(int k=j+1;k<=m;k++)
				if(check(i,j,k))//调用函数检查
					ans++;
	cout<<ans；//切勿抄袭
	return 0;
}
```


---

## 作者：Kalium (赞：1)

# P3670【[USACO17OPEN]Bovine Genomics S】题解

这题难度不大，主要是题面问题（我就是题面理解$1h$，代码只需$15min$）

进入正题

## 题意：

就是给定 $2$ 份串，一份是斑点的，一份无斑点的，问在这些串中，在有斑点的寻找一个三元组合 ${a[i],a[j],a[k]}$，在无斑点的寻找一个三元组合 ${b[i],b[j],b[k]}$，如果有字母不同$ans$加一，问你最后$ans$是多少

但是，${a[i],a[j],a[k]}$ 与 ${b[i],b[k],b[j]}$ 本质上相同，只能算一种，即你如果 ${a[i],a[j],a[k]}$ 与 ${b[i],b[j],b[k]}$ 算了一种，那么${a[i],a[j],a[k]}$与 ${b[i],b[k],b[j]}$ 就不能算上去

## 思路：

题目解释完了，就很容易了

先用 $a$ 数组把有斑点的串把里面的字母用$1$，$2$，$3$，$4$分别代替

再用 $b$ 数组把无斑点的串把里面的字母用$1$，$2$，$3$，$4$分别代替

随即开始暴力枚举，用 $flag$ 数组表示当前的有斑点的三个字母元素状态，再在无斑点串中的相同位置判断是否相同即可

## 代码（CODE）

```cpp
#include <iostream>
#include <cstring>
#define ri register int//装x用

using namespace std;

const int N = 5e2 + 7, M = 5e1 + 7;//也是装x

char x;
int a[N][M];
int b[N][M];
int n, m;

inline int change(char x) {//inline还是装x
	if (x == 'A')
		return 1;
	if (x == 'C')
		return 2;
	if (x == 'G')
		return 3;
	if (x == 'T')
		return 4;
}

int main() {
	cin >> n >> m;
	for (ri i = 1; i <= n; i ++) {
		for (ri j = 1; j <= m ; j++) {
			cin >> x;
			a[i][j] = change(x);
		}
	}
	for (ri i = 1; i <= n; i ++) {
		for (ri j = 1; j <= m; j ++) {
			cin >> x;
			b[i][j] = change(x);
		}
	}
	bool flag[5][5][5];
	int ans = 0;
	for (ri i = 1; i <= m - 2; i ++) {
		for (ri j = i + 1; j <= m - 1; j ++) {
			for (ri k = j + 1; k <= m; k ++) {
				bool tf = 0;
				memset(flag, 0, sizeof(flag));
				for (ri l = 1; l <= n; l ++)
					flag[a[l][i]][a[l][j]][a[l][k]] = 1;
				for (ri l = 1; l <= n; l ++) {
					if (flag[b[l][i]][b[l][j]][b[l][k]]) {
						tf = 1;
						break;
					}
				}
				//cout << ans << endl;
				if (!tf)
					ans ++;
			}
		}
	}
	cout << ans << endl;
	return 0;
}
```
AFO选手作品


---

## 作者：sycqwq (赞：1)

~~语文~~暴力题

$o(n^3m)$

枚举，然后在判断是否可行即可

```cpp
#include<bits/stdc++.h>
#define read() Read<int>()
namespace pb_ds{//祖传快读
    namespace io{
        const int MaxBuff=1<<15;
        const int Output=1<<23;
        char B[MaxBuff],*S=B,*T=B;
        #define getc() ((S==T)&&(T=(S=B)+fread(B,1,MaxBuff,stdin),S==T)?0:*S++)
        char Out[Output],*iter=Out;
        inline void flush(){
            fwrite(Out,1,iter-Out,stdout);
            iter=Out;
        }
    }
    template<class Type> inline Type Read(){
        using namespace io;
        register char ch;
        register Type ans=0;
        register bool neg=0;
        while(ch=getc(),(ch<'0' || ch>'9') && ch!='-');
        ch=='-'?neg=1:ans=ch-'0';
        while(ch=getc(),'0'<= ch && ch<='9') ans=ans*10+ch-'0';
        return neg?-ans:ans;
    }
    template<class Type> inline void Print(register Type x,register char ch='\n'){
        using namespace io;
        if(!x) *iter++='0';
        else{
            if(x<0) *iter++='-',x=-x;
            static int s[100];
            register int t=0;
            while(x) s[++t]=x%10,x/=10;
            while(t) *iter++='0'+s[t--];
        }
        *iter++=ch;
    }
}
using namespace pb_ds;
using namespace std;
typedef long long ll;
const int maxn=1e3+5;
int n,m;
char a[maxn][maxn],b[maxn][maxn];
bool bk[11115]; 
int main(){

    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    cin>>n>>m;
    for(int i=1;i<=n;i++)
    {
        cin>>a[i]+1;
    }
    for(int i=1;i<=n;i++)
    {
        cin>>b[i]+1;
    }
    int s=0;
    for(int i=1;i<=m-2;i++)
    {

        for(int j=i+1;j<=m-1;j++)
            for(int k=j+1;k<=m;k++)
            {
                memset(bk,0,sizeof bk);
                for(int l=1;l<=n;l++)//基因打标记
                {
                    bk[a[l][i]*100+a[l][j]*10+a[l][k]]=1;
                }
                int f=1;
                for(int l=1;l<=n;l++)//判断
                {
                    if(bk[b[l][i]*100+b[l][j]*10+b[l][k]])
                    {
                        f=0;
                        break;  
                    }

                }
                if(f)
                {
                    ++s;
                }
            }
    }

    cout<<s;
    return 0;
}
```

---

## 作者：Zenith_Yeh (赞：1)

这就是暴力。。。

我们枚举三元组，再枚举每一个奶牛(因为只有四个字符，所以可以用1到444来表示字符串)，依次判断即可。

**上菜：**
```cpp
#include<bits/stdc++.h>
inline int read()
{	int x=0;
	bool f=0;
	char c=getchar();
	while(!isdigit(c))f|=(c=='-'),c=getchar();
	while(isdigit(c))x=x*10+(c&15),c=getchar();
	return f?-x:x;
}
using namespace std;
int n,m,spotty[505][505],plain[505][505],dl[505],cnt,ans;
bool bj[445];
int main()
{	n=read(),m=read();
	for(register int i=1;i<=n;++i)
		for(register int j=1;j<=m;++j)
		{	char c;
			cin>>c;
			switch(c)
			{	case 'A':spotty[i][j]=1;break;
				case 'C':spotty[i][j]=2;break;
				case 'G':spotty[i][j]=3;break;
				case 'T':spotty[i][j]=4;break;
			}
		}
	for(register int i=1;i<=n;++i)
		for(register int j=1;j<=m;++j)
		{	char c;
			cin>>c;
			switch(c)
			{	case 'A':plain[i][j]=1;break;
				case 'C':plain[i][j]=2;break;
				case 'G':plain[i][j]=3;break;
				case 'T':plain[i][j]=4;break;
			}
		}
	for(register int i=1;i<=m;++i)
		for(register int j=i+1;j<=m;++j)
			for(register int k=j+1;k<=m;++k)
			{	cnt=0;
				for(register int l=1;l<=n;++l)
					if(!bj[spotty[l][i]*100+spotty[l][j]*10+spotty[l][k]])
					{	bj[spotty[l][i]*100+spotty[l][j]*10+spotty[l][k]]=1;
						dl[++cnt]=spotty[l][i]*100+spotty[l][j]*10+spotty[l][k];
					}
				for(register int l=1;l<=n;++l)
					if(bj[plain[l][i]*100+plain[l][j]*10+plain[l][k]])
					{	ans++;
						break;
					}
				for(register int l=1;l<=cnt;++l)bj[dl[l]]=0;
			}
	cout<<m*(m-1)*(m-2)/6-ans;
	return 0;
}

```


---

## 作者：whc2020 (赞：1)

题意：

给定n个A类字符串，n个B类字符串。

统计所有的 三元组 (i , j , k) ，使得 三元组(a[i] , a[j] , a[k]) 不同于 三元组(b[i] , b[j] , b[k]) （a是任意一个A类字符串 ， b是任意一个B类字符串）。

解题思路：

枚举所有的三元组 (i , j , k) ， 再进行判断 ， 。



代码：

```cpp
#include<bits/stdc++.h>
using namespace std;

int n , m , ans;
int a[1005][55];
bool h[5][5][5];

int f (char x) {//将原本的“ACGT”进行压缩，便于h数组的存储与检验。
	switch (x) {
		case 'A' : {
			return 1;
			break;
		}
		case 'C' : {
			return 2;
			break;
		}
		case 'G' : {
			return 3;
			break;
		}
		case 'T' : {
			return 4;
			break;
		}
	}
}

int main () {
	scanf ("%d%d" , &n , &m);
	for (int i = 1 ; i <= 2 * n ; i++) {
		char temp;
		scanf ("%c" , &temp);//读入每行前的换行符。
		for (int j = 1 ; j <= m ; j++) {
			scanf ("%c" , &temp);
			a[i][j] = f (temp);//压缩成小于等于4的正整数
		}
	}
	for (int i = 1 ; i <= m ; i++) {
		for (int j = i + 1 ; j <= m ; j++) {
			for (int k = j + 1 ; k <= m ; k++) {//枚举三元组(i , j , k)。
				bool flag = 1;
				memset (h , 0 , sizeof (h));//每次h数组使用完后需要初始化。
				for (int l = 1 ; l <= n ; l++) {
					h[a[l][i]][a[l][j]][a[l][k]] = 1;//直接用基因的种类（ACGT）压缩后的正整数当做下标，便于直接修改与查询。
				}
				for (int l = n + 1 ; l <= 2 * n ; l++) {
					if (h[a[l][i]][a[l][j]][a[l][k]] == 1) {
						flag = 0;
						break;
					}
				}
				if (flag == 1) {
					ans++;
				}
			}
		}
	}
	printf ("%d" , ans);
	return 0;
}
```


---

## 作者：Tatayy (赞：1)

#### ~~发现没人用set试发题解zuo~~

这题有**两种**解法：

***1.*** STL 的 *set*

***2.*** 哈希（或者是说映射）表

----

分析：

**set**

set使用红黑树，插入和查找基本都是O(logn)。
加上三重循环枚举位置和嵌套在内的一重循环插入和查找，时间复杂度为O(m * m * m * n * logn)，数据特别大便会超时（最坏情况为O(1e+9)）。

----

**哈希映射**

记录和查找都是常数级（O(1)），同上四重循环，时间复杂度为O(m * m * m * n)，可以通过此题。

----

&nbsp;

----

### 上代码：

***1.*** set

```cpp
#include<set>
#include<iostream>
#include<algorithm>
using namespace std;
const int N=500+5;
string g[2*N];
int n,m,ans;
string makestring(const string& str,const int& p1,const int& p2,const int& p3) // 取str的p1、p2、pe三个位置的字符并合成一个字符串
{
    string tmp;
    tmp.push_back(str[p1]);
    tmp.push_back(str[p2]);
    tmp.push_back(str[p3]);
    return tmp;
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0); // 本萌新瞎写的一大堆优化（可是没啥用，read快读更快）
    cin>>n>>m;
    for(int i=1; i<=2*n; ++i) cin>>g[i];
    for(int p1=0; p1<m; ++p1)
        for(int p2=p1+1; p2<m; ++p2)
            for(int p3=p2+1; p3<m; ++p3) // 三重循环枚举基因串上的每个位置
            {
                set<string> dict; // 也可以用mutiset
                for(int x=1; x<=n; ++x)
                {
                    string t=makestring(g[x],p1,p2,p3);
                    if(!dict.count(t)) dict.insert(t); // 实际上不需要if
                }
                bool fail=false;
                for(int x=n+1; x<=n*2; ++x)
                    if(dict.count(makestring(g[x],p1,p2,p3))) // 如果出现过
                    {
                        fail=true;
                        break;
                    }
                if(!fail) ++ans;
            }
    cout<<ans<<endl;
    return 0;
}
```
----
***2.*** 哈希映射
```cpp
#include<cstring>
#include<vector>
#include<iostream>
using namespace std;
vector<string> cows; // vector存储
bool flag[30][30][30]; // 26个字母转化为0-25
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int n,m,ans=0;
    cin>>n>>m;
    for(int i=0; i<2*n; i++)
    {
        string str;
        cin>>str;
        cows.push_back(str);
    }
    for(int i=0; i<m; i++)
        for(int j=i+1; j<m; j++)
            for(int k=j+1; k<m; k++)
            {
                memset(flag,0,sizeof(flag));
                for(int s=0; s<n; s++) flag[cows[s][i]-'A'][cows[s][j]-'A'][cows[s][k]-'A']=true; // 记录
                bool ok=true;
                for(int s=n; s<2*n; s++)
                    if(flag[cows[s][i]-'A'][cows[s][j]-'A'][cows[s][k]-'A'])
                    {
                        ok=false;
                        break;
                    }
                if(ok) ans++;
            }
    cout<<ans<<endl;
    return 0;
}
```
#### 求大佬高见**qwq**

---

## 作者：2021changqing52 (赞：1)

### 思路
先暴力枚举三个位点，再开三维数组判断两类牛是否有这三个位点相同的。（有点暴力）
### Code:
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,m,a[501][50],b[501][50],t[5][5][5],ans;//t数组是判断用的数组
char x;bool f;
int get(char x){
    if(x=='A')return 1;
    if(x=='C')return 2;
    if(x=='G')return 3;  
    if(x=='T')return 4;
}
int main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++){
    	for(int j=1;j<=m;j++){
            cin>>x;
            a[i][j]=get(x); 
        }
    }
    for(int i=1;i<=n;i++){
    	for(int j=1;j<=m;j++){
            cin>>x;
            b[i][j]=get(x);
        }
    }
    for(int i=1;i<=m-2;i++){//枚举
    	for(int j=i+1;j<=m-1;j++){
    		for(int k=j+1;k<=m;k++){
                f=1;//判断
                memset(t,0,sizeof(t));
                for(int x1=1;x1<=n;x1++)t[a[x1][i]][a[x1][j]][a[x1][k]]=1;     
                for(int x2=1;x2<=n;x2++)
		if(t[b[x2][i]][b[x2][j]][b[x2][k]]){f=0;break;}     
                if(f)ans++;
            }
    	}
    }
    cout<<ans;
    return 0;
}
```

---

## 作者：羚羊WANG (赞：0)

[题目传输门](https://www.luogu.com.cn/problem/P3670)

有$n$个长度为$m$的有斑点串,和$n$个长度为$m$的有无斑点串

题目的要求是让我们求有多少个三元组区分斑点串

显然，最暴力的思路就是枚举三个点，然后判断这个三元组是否合法

时间复杂度$O(n^3m)$

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read()
{
	int x=0;
	bool f=0;
	char c=getchar();
	while (!isdigit(c))
		  f|=(c=='-'),c=getchar();
	while (isdigit(c))
		  x=(x<<3)+(x<<1)+(c^48),c=getchar();
	return f?-x:x;
}
void write(int x) {
    if(x<0) {
        putchar('-');
        x=-x;
    }
    if(x>9) write(x/10);
    putchar(x%10+'0');
}
int n;
int Size;
inline int change(char a){
	if(a=='A')
		return 1;
	if(a=='C')
		return 2;
	if(a=='G')
		return 3;
	if(a=='T')
		return 4;
}
int e1[510][510];
int e2[510][510];
int f[10][10][10];
char a[510];
int ans;
signed main(){
	n=read();
	Size=read();
	for(register int i=1;i<=n;++i)
		{
			scanf("%s",a+1);
			for(register int j=1;j<=Size;++j)
				e1[i][j]=change(a[j]);
		}
	for(register int i=1;i<=n;++i)
		{
			scanf("%s",a+1);
			for(register int j=1;j<=Size;++j)
				e2[i][j]=change(a[j]);
		}
	for(register int i=1;i<=Size-2;++i)
		for(register int j=i+1;j<=Size-1;++j)
			for(register int k=j+1;k<=Size;++k)
				{
					memset(f,0,sizeof(f));
					bool flag=1;
					for(register int l=1;l<=n;++l)
						f[e1[l][i]][e1[l][j]][e1[l][k]]=1;
					for(register int l=1;l<=n;++l)
						if(f[e2[l][i]][e2[l][j]][e2[l][k]])
							{
								flag=0;
								break;
							}
					if(flag)	
						ans++;
				}
	write(ans);
	return 0;
}

```

最后祝大家AC此题


---

## 作者：Six_chestnuts (赞：0)

题意
------------
给定 $2$ 组字符串，每组 $n$ 个，每个字符串包含 $m$ 个字符。

我们称一个三元组 $(i,j,k)$ 是合法的，当且仅当第二组的每个字符串中下标为 $(i,j,k)$ 的字符拼成的字符串与第一组的每个字符串中下标为 $(i,j,k)$ 的字符拼成的字符串均不相等。

现在需要你对于给定的 $2$ 组字符串，找出所有合法的三元组 $(i,j,k)$ 的数量。


------------
具体思路见代码
------------
```c
#include<bits/stdc++.h>
using namespace std;
int ans=0,m,n;	//ans代表方法的数量，n和m是题目中所述的变量
int vis[10][10][10];	//vis数组代表本质的数字排列的顺序有则是true没有是false
int y[505][55],w[505][55],num[30];		//y数组代表有斑点的牛的数字，w数组代表没有斑点的牛的数字，num数组保存将字符转换数字下标是字符的位置存的是字符对应的数字
bool check(int i,int j,int k)		//读入三个本质的位置
{
	memset(vis,0,sizeof(vis));	//清空
	for(int h=1;h<=n;h++)		//枚举每一个有斑点的牛的数字
		vis[y[h][i]][y[h][j]][y[h][k]]=1;		//打上标记
	for(int h=1;h<=n;h++)		//枚举每一个没有斑点的牛的数字
		if(vis[w[h][i]][w[h][j]][w[h][k]]==1)		//如果有标记则代表重复了
			return false;		//返回结果
	return true;	//返回结果
}
int main()
{
	cin>>n>>m;		//输入
	num['A'-'A'+1]=1,num['C'-'A'+1]=2,num['G'-'A'+1]=3,num['T'-'A'+1]=4;	//定义每一个英文字母代表的数字
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)	//输入
		{
			char a;
			cin>>a;		//输入
			y[i][j]=num[a-'A'+1];	//将数字存入数组中
		}
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)	//输入
		{
			char a;
			cin>>a;		//输入
			w[i][j]=num[a-'A'+1];		//将数字存入数组中
		}
	}
	for(int i=1;i<=m;i++)
		for(int j=i+1;j<=m;j++)
			for(int k=j+1;k<=m;k++)		//枚举这三个本质的位置
				if(check(i,j,k)==true)	//如果这枚举的三个本质的位置合法则将答案++
					ans++;
	cout<<ans;		//输出答案
	return 0;
 }
```


---

