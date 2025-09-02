# Marks

## 题目描述

总的来说，这个小组有$N$个学生。他们获得了$M$科目的分数。每个学生从每个科目的$1$分到$9$分（包括$1$分）得了一分。

如果没有学生在这个科目上获得更高的分数，我们就可以认为这个学科这个学生是最擅长的。如果存在一个他最擅长的学科，那么这个学生就是成功的。

你的任务是找出小组中成功学生的人数。

## 说明/提示

在第一个样例中，$1$号学生是最好的科目是$1$和$3$，$2$号学生是最好的科目$1$和$2$，但$3$号学生没有任何科目最好。

在第二个样例中，每个学生至少有一个科目是最好的。

Translated by Khassar

## 样例 #1

### 输入

```
3 3
223
232
112
```

### 输出

```
2
```

## 样例 #2

### 输入

```
3 5
91728
11828
11111
```

### 输出

```
3
```

# 题解

## 作者：Yaixy (赞：6)

# 题意及注意点

- 给出 $n$ 个字符串，每个字符串 $S_i$ 中有 $m$ 个在 $1$ 到 $9$ 之间的字符，若**任意**一个字符为 $n$ 组数据中**同一位置**字符的最大值，第 $i$ 个学生即为成功学生。求这种成功学生的人数。 

- 最高分有**并列**的情况，这种情况下每个并列最高分都是成功学生。

- $n$ 和 $m$ 均不小于 $1$，不大于 $100$。

- **二维数组别开成一维数组！**（这大概是只有我会犯的sb错误了/kk

# 解题思路

- 最容易发现的一点：正解是**模拟**

- 这道题其实做下去都比较顺，所以唯一要做的就是理清思路，避免像yxy一样的小错误qwq

1. 输入 $n$ 和 $m$，同时输入 $n$ 个字符串 $S_i$。

- 在输入 $S_i$ 时还要进行单个字符的处理，将字符的值传进数组中；同时不断更新每门科目的最大值 $Max$。

2. 重新扫一遍数组，记下每门科目的成功学生。

1. ~~再扫一遍数组~~，判断成功学生的个数，更新计数器。

其他具体操作可以见代码qwq

# 代码

- 马蜂稍有点诡异，应该不影响大局awa（

```cpp
#include<bits/stdc++.h>
using namespace std;
string s;
int n,m,Max[205],a[205][505],ans;
bool flag;
int main()
{
	cin>>n>>m;
	for(int i=1;i<=n;i++)
	 {
	 	cin>>s;
	 	for(int j=0;j<m;j++) a[i][j+1]=s[j]-'0';
	 	for(int j=1;j<=m;j++) if(a[i][j]>Max[j]) Max[j]=a[i][j];
	 }
	for(int i=1;i<=n;i++)
	 for(int j=1;j<=m;j++) if(a[i][j]>=Max[j]) a[i][j]=0;
	for(int i=1;i<=n;i++)
	 {
	 	flag=false;
	 	for(int j=1;j<=m;j++) if(a[i][j]==0) flag=true;
	    if(flag==true) ans++;
	 }
	cout<<ans<<endl;
	return 0;
}
```

撒花完结qwq

---

## 作者：Suuon_Kanderu (赞：2)

这就是个模拟。

没什么可讲的了，只告诉大家没有空格如何输入数字
```
		scanf("%1d",&a[i][j]);//比字符数组easy
```


代码



```
#include<iostream>
#include<cstring>
using namespace std;
int main()
{
	int a[101][101];
	int n,m;
	cin>>n>>m;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
	{
		scanf("%1d",&a[i][j]);//输入神奇
	}
	bool t[101];//用一个桶来看那个同学优秀
	memset(a,0,sizeof(t));//清零
	for(int j=1;j<=m;j++)
		{
			int ans=-1,k=1;
			for(int i=1;i<=n;i++)
			if(a[i][j]>=ans)
			{
				ans=a[i][j];
				k=i;

			}
			for(int i=1;i<=n;i++)//关键，过会说
			{
				if(a[i][j]==ans)
				t[i]=true;	
			}
		}
	int aa=0;
	for(int i=1;i<=n;i++)
	{
		if(t[i])++aa;
	}
	cout<<aa<<endl;
	return 0;
}
        

}
```
这里注意了，如果有多个最高分，他们都很优秀。

~~所以关键那步是很关键的~~

亲测AC放心



---

## 作者：Allanljx (赞：1)

## 思路
暴力枚举每个人的每门成绩，如果没有比这个人成绩高的， $ans$ 就加$1$。
## 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
int a[105][105],ans;//a[i][j]表示第i个人第j门成绩
int main()
{
	int n,m,f;
	cin>>n>>m;
	for(int i=1;i<=n;i++)
	{
		string s;
		cin>>s;
		for(int j=0;j<m;j++)
		{
			a[i][j+1]=s[j]-'0';//转为int型
		}
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			f=0;
			for(int k=1;k<=n;k++)
			{
				if(k==i) continue;//自己和自己比
				if(a[k][j]>a[i][j])//有分比当前这个人高的
				{
					f=1;break;
				}
			}
			if(f==0)//如果没有比他成绩高的
			{
				ans++;break;
			}
		}
	}
	cout<<ans<<endl; 
	return 0;
}
```


---

## 作者：Creator_157 (赞：1)

### 大题题意：

给你一个矩阵，寻找每一列中最大的数，看分布在多少个排中。

------------
### 具体思路：

在输入时标记好每一列的最大值，最后扫一遍数组，累加计数即可。

------------
### code：

一些细节在代码注释中。

```cpp
#include<iostream>
#include<cmath>
#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
int n,m,ans;
int v[102];
char a[102][102];
int ma[102];
int main()
{
	cin>>n>>m;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			cin>>a[i][j];//运用字符类型可以解决没有空格的问题
			int y=a[i][j]-'0';//巧用ASCLL
			ma[j]=max(y,ma[j]);//寻找每列的最大值
		}
	}
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			if(a[i][j]-'0'==ma[j]&&v[i]==0)
			{
				v[i]=1;//防止重复统计
				ans++;
			}
		}
	}
	cout<<ans;
	return 0;
}

```

---

## 作者：Register (赞：1)

## 需要注意一点小细节
下述都是我的想法：
1. 读入成绩时是没有空格的，因此可以使用char类型，减去48后就能得到一个值
2. 对于每一个科目，并列第一的学生也可以算作成功的，本人就在这里卡了一下，所以必须用数组储存

说的也差不多了，上代码：
```cpp
#include <iostream>
using namespace std;
bool pd[101];
int a[101][101];
int main(){
	int n,m,sum=0;
	char c;
	cin>>n>>m;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++) {cin>>c;a[i][j]=c-48;}//全部放进int数组，方便比较
	for(int i=1;i<=m;i++)
	{
		int s=0/*并列人数的计数器*/,maxi[101]={0}/*编号统计*/,maxn=0/*最大值*/;
		for(int j=1;j<=n;j++)//全部遍历
			if(a[j][i]==maxn) maxi[++s]=j;//并列就新增一个
			else if(a[j][i]>maxn) {s=1;maxn=a[j][i];maxi[s]=j;}//超过了当前最佳就重置
		for(int j=1;j<=s;j++) pd[maxi[j]]=true;//标记成功的学生
	}
	for(int i=1;i<=n;i++)
		if(pd[i]) sum++;//统计成功学生的个数
	cout<<sum<<endl;
	return 0;
}
```

---

## 作者：Trollz (赞：0)

~~这么水的题我卡了一个上午~~

这个连算法都不要，暴力模拟就好。

更多解释看注释。

/**/里面的是我的错误示范

$\color{purple}\text{Code:}$
```cpp
#include <iostream>
#include <string.h>
#include <algorithm>
using namespace std;
char a[1001][1001];
int b[1001][1001];
bool maxn[1001];
int main(){
	memset(maxn,false,sizeof(maxn));
	int n,m;
	cin>>n>>m;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			cin>>a[i][j];
		}
	}//由于不能空格，所以我们先用字符存起来，然后转化为数字
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			b[i][j]=a[i][j]-48;
		}
	}//转化为数字
	int tmp;//记录最大值
	/*int xiabiao=0;*/
	for(int i=1;i<=m;i++){
		tmp=-1;//每个科目的成绩遍历后，归为-1（万一最高分0分）
		for(int j=1;j<=n;j++){
			tmp=max(tmp,b[j][i])；
		}//先找最大值
		for(int j=1;j<=n;j++){
			if(b[j][i]==tmp){
				maxn[j]=true;
			}
		}//如果发现多个同学并列第一，全部标为true
		/*cout<<tmp<<" ";*/
		
		/*for(int i=1;i<=m;i++){
			tmp=-200;
			if(b[i][j]>tmp){
				xiabiao=i;	
				tmp=b[i][j]; 
			}
			if(b[i][j]==tmp){
				maxn[j]=1;
			}
		}*/
		/*maxn[xiabiao]=1;*/
	}
	int ans=0;
	for(int i=1;i<=n;i++){
		/*cout<<i<<" "<<maxn[i]<<endl;*/
		if(maxn[i]!=false){
			ans++;
		}
	}//发现为true，ans加1
	cout/*<<endl*/<<ans<<endl;
	return 0;
}
```

亲测$AC$，放心食用

---

## 作者：Eason_AC (赞：0)

## Content
有 $n$ 名学生考了 $m$ 门科目，各得到了自己的成绩单。如果第 $i$ 个学生的第 $j$ 个科目的分数 $a_{i,j}$ 在所有学生中是最高的，那么我们就说这名学生在这门科目上是擅长的。如果第 $i$ 名学生至少有一门擅长的科目，那么我们就说这名学生是成功的。求有多少名学生是成功的。

**数据范围：$1\leqslant n,m\leqslant100,1\leqslant a_{i,j}\leqslant9$。**
## Solution
我们先处理出每个科目最高的分数，再倒回去遍历看每名学生在这门科目上所得到的分数是否是所有学生中最高的，这样就记录出所有成功的学生的人数了。

注意，这里数字的读入是没有空格的。所以我们需要用到 $\texttt{scanf}$ 中的奇技淫巧——按位读入。具体去代码里看吧。
## Code
```cpp
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <iostream>
using namespace std;

int n, m, ans, a[107][107], maxi[107], suc[107];

int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; ++i)
		for(int j = 1; j <= m; ++j) {
			scanf("%1d", &a[i][j]);
			maxi[j] = max(maxi[j], a[i][j]);
		}
	for(int i = 1; i <= n; ++i) {
		for(int j = 1; j <= m; ++j)
			if(maxi[j] == a[i][j]) {
				suc[i] = 1;
				break;
			}
		ans += suc[i];
	}
	printf("%d", ans);
}
```

---

## 作者：TLMPEX (赞：0)

思路：枚举每一门课每一个人的成绩，用一个变量来记录这门课的最高分，看有多少个人等于最高分，等于最高分这个人就标记为一，最后看有多少个人得过最高分，得过最高分的，成功的人数加一。

```c
#include<bits/stdc++.h>
using namespace std;
int a[101][101],b[101];
int main(){
	int n,m,x,i,j,z=0;
	cin>>n>>m;
	for(i=1;i<=n;i++)
		for(j=1;j<=m;j++)
			scanf("%1d",&a[i][j]);
	for(i=1;i<=m;i++){
		x=0;//把x清0
		for(j=1;j<=n;j++)
			if(a[j][i]>x)x=a[j][i];//取这门课成绩的最高分
		for(j=1;j<=n;j++)
			if(a[j][i]==x)b[j]=1;//看有多少人这门课获得最高分，获得的人就把那个人标记为1
	}
	for(i=1;i<=n;i++)
		if(b[i])z++;//如果这个人获得过最高分，则成功人数加一
	cout<<z;
}
```


---

## 作者：TRZ_2007 (赞：0)

### 题解 [CF152A 【Marks】](https://www.luogu.com.cn/problem/CF152A)  
# Solution  
其实这道题目非常的有意思，但是不要忘了它有众多的坑点。  
- 1：他们的成绩之间是没有空格的，但是这点我们可以用```scanf("%1d",&a[i][j];```这个~~玄学的~~东西来解决。  

- 2：他们的科目是竖着排的，这证明我们需要先枚举竖排再枚举横排。  

- 3：每个科目并列第一的人都很优秀，我们都要把他们算进来。

- 4：优秀过一次的人不能再优秀，所以我们要用```flag```来标记。  


这些坑点过去了就可以愉快地写代码了！  

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 109;

int a[N][N],flag[N];
int n,m,Max[N],ans;

template<class T>
inline void read(T& x) {
	x = 0;
	char ch = getchar();
	while(ch < '0' || ch > '9') {
		ch = getchar();
	}
	while(ch >= '0' && ch <= '9') {
		x = x * 10 + ch - '0';
		ch = getchar();
	}
}

int main() {
	read(n);read(m);
	for(int i = 1;i <= n;i++) {
		for(int j = 1;j <= m;j++) {
			scanf("%1d",&a[i][j]);
		}
	}
	for(int i = 1;i <= m;i++) {
		for(int j = 1;j <= n;j++) {
			Max[i] = max(Max[i],a[j][i]);
		}
	}
	for(int i = 1;i <= m;i++) {
		for(int j = 1;j <= n;j++) {
			if(a[j][i] == Max[i] && !flag[j]) {
				ans++;
				flag[j] = 1;
			}
		}
	}
	printf("%d\n",ans);
	return 0;
}
```

---

## 作者：Cesare (赞：0)

一道水题。

思路是读入所有人的成绩，算出来各科最高之后再算有多少人有最高，注意字符串读入的下标即可。

```	cpp
#include <bits/stdc++.h>
#define re register
#define For(i,j,k) for(re int i=j;i<=k;i++)
using namespace std;
typedef long long ll;

ll n,m,ans[110],num[110][110],sum=0;
string mp[110];

inline ll read(){
    ll x=0;bool f=0;char ch=getchar();
    for(;!isdigit(ch);ch=getchar())f^=(ch=='-');
    for(;isdigit(ch);ch=getchar())x=(x<<3)+(x<<1)+(ch^48);
    return f? -x: x;
}

int main() {
    n=read(),m=read();
    for(re int i=1;i<=n;i++){
        getline(cin,mp[i]);
    }
    for(re int i=1;i<=n;i++){
        for(re int j=0;j<m;j++){
            if(mp[i][j]-'0'>ans[j]){ans[j]=mp[i][j]-'0';}
        }
    }
    for(re int i=1;i<=n;i++)
        for(re int j=0;j<m;j++)//下标从零开始
            if(mp[i][j]-'0'==ans[j]){sum++;break;}
    cout<<sum<<endl;
    return 0;
}

```

---

