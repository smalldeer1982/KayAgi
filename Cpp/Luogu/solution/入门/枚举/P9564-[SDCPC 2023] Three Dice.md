# [SDCPC 2023] Three Dice

## 题目描述

骰子，是一种各面带有标记，以生成随机数的小型可投掷道具，通常用于桌上游戏。

![](https://cdn.luogu.com.cn/upload/image_hosting/dsezqcgm.png)

最常见的骰子是一种小正方体，每个面上被标记了从 $1$ 到 $6$ 的数字。数字 $n$（$1 \le n \le 6$）通常由 $n$ 个小圆点组成的图案来表示，其中 $1$ 号与 $4$ 号面的小圆点是红色的，而 $2$, $3$, $5$ 与 $6$ 号面的小圆点是黑色的。

小青鱼手中有三只骰子。有一天，他将这三只骰子投掷在桌子上，并观察了朝上的那一个面。他发现所有朝上的面中，红色的点数之和恰好为 $A$，而黑色的点数之和恰好为 $B$。

然而，您对小青鱼的发现感到怀疑。您想要确认是否有可能投掷出三只骰子，使得所有朝上的面中，红色的点数之和恰好为 $A$，而黑色的点数之和恰好为 $B$。

## 样例 #1

### 输入

```
4 5
```

### 输出

```
Yes
```

## 样例 #2

### 输入

```
3 0
```

### 输出

```
Yes
```

## 样例 #3

### 输入

```
1 2
```

### 输出

```
No
```

# 题解

## 作者：Dws_t7760 (赞：6)

可以发现本题中只有三个骰子，情况较少，可以枚举各种情况，判断是否有方案。

代码如下：

```cpp
#include<iostream>
using namespace std;
int a,b;
string y="Yes",n="No";
int main() {
	cin>>a>>b;
	if(a==0) {
		if(b==7||b==8||b==12||b==16||b==17||b==6||b==9||b==15||b==18||b==10||b==11||b==13||b==14) cout<<y;
		else cout<<n;
	}
	else if(a==1||a==4) {
		if(b==4||b==5||b==6||b==7||b==8||b==10||b==11||b==12) cout<<y;
		else cout<<n;
	}
	else if(a==2||a==5||a==8) {
		if(b==2||b==3||b==5||b==6) cout<<y;
		else cout<<n;
	}
	else if(a==3||a==6||a==9||a==12) {
		if(b==0) cout<<y;
		else cout<<n;
	}
	else cout<<n;
	return 0; 
}
```


---

## 作者：zly2009 (赞：5)

题目已知有 $3$ 个骰子，每个骰子有 $6$ 个面，显然三重循环可以过。

三重循环依次枚举一下每个骰子的点数，按点数对应的颜色分别累加，如果满足输入的点数之和即 `Yes`；如果一直没有则 `No`。

代码如下：

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
bool book[7]={0,0,1,1,0,1,1};
int A,B;
void cnt(int x)
{
	if(!book[x])A+=x;
	else B+=x;
}
signed main()
{
	int a,b;
	cin>>a>>b;
	bool ok=0;
	for(int i=1;i<=6;i++)
		for(int j=1;j<=6;j++)
			for(int k=1;k<=6;k++){
				A=0,B=0;
				cnt(i),cnt(j),cnt(k);
				if(A==a&B==b){
					ok=1;
					break;
				}
			}
	cout<<(ok?"Yes":"No");
}
```

---

## 作者：scp020 (赞：2)

# P9564 [SDCPC2023] I-Three Dice 题解

签到题，是这场比赛最简单的题。

## 解法

因为只有三个骰子，所以我们考虑用 $3$ 层循环去枚举这三种骰子哪面朝上的情况，然后判断每种情况是否满足条件。解法说明在下面代码里。

### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int a,b,suma,sumb;
// 这个函数返回当一个骰子朝上点数为 a 时红色或黑色点数有几个，type = 1 时返回红色点数，type = 2 时返回黑色点数
inline int judge(int a,int type)
{
	// 询问 a 点朝上时红色点数有几个，如果是 1 或 4 则返回相应点数，否则返回 0
	if(type==1)
	{
		if(a==1) return 1;
		if(a==4) return 4;
		return 0;
	}
	// 询问 a 点朝上时黑色点数有几个，如果是 2 或 3 或 5 或 6 则返回相应点数，否则返回 0
	if(a==2) return 2;
	if(a==3) return 3;
	if(a==5) return 5;
	if(a==6) return 6;
	return 0;
}
int main()
{
	cin>>a>>b;
	for(int i=1;i<=6;i++)
	{
		for(int j=1;j<=6;j++)
		{
			for(int k=1;k<=6;k++)
			{
				// 计算当前情况的红色点数和黑色点数
				suma=judge(i,1)+judge(j,1)+judge(k,1),sumb=judge(i,2)+judge(j,2)+judge(k,2);
				// 有情况满足条件
				if(suma==a && sumb==b)
				{
					cout<<"Yes";
					return 0;
				}
			}
		}
	}
	// 没有情况满足条件
	cout<<"No";
	return 0;
}
```

---

## 作者：Not_defined (赞：2)

题目大意：一个骰子，其 $1$ 号面和 $4$ 号面是红色的，其余面是黑色的。给出两个整数 $A$ 和 $B$，分别表示朝上的红色点数之和与黑色点数之和，如果小青鱼有可能投掷出三只骰子使得所有朝上的面中，红色的点数之和恰好为 $A$，而黑色的点数之和恰好为 $B$，则输出 $\texttt Yes$，否则输出 $\texttt No$。

分析：本题数据范围较小，将红色点数与黑色点数分别存进两个数组里，分别用   $cnt1$ 和 $cnt2$ 标记当前红黑点数和， $tot$ 表示当前投了几个骰子，直接爆搜。

### My code
```c
#include<bits/stdc++.h>
using namespace std;
int a,b,A[3],B[5];
bool flag;
void dfs(int cnt1,int cnt2,int tot)
{
	if(cnt1>a||cnt2>b||tot>3)return;
	if(cnt1==a&&cnt2==b&&tot==3)flag=1;
	if(cnt1<a)
		for(int i=1;i<=2;i++)dfs(cnt1+A[i],cnt2,tot+1);
	if(cnt2<b)
	    for(int i=1;i<=4;i++)dfs(cnt1,cnt2+B[i],tot+1);
}
int main()
{
	cin>>a>>b;
	A[1]=1,A[2]=4,B[1]=2,B[2]=3,B[3]=5,B[4]=6;
	dfs(0,0,0);
	if(flag)puts("Yes");
	else puts("No");
	return 0;
}
// 1 4
// 2 3 5 6
```


---

## 作者：DHeasy (赞：2)

分类讨论红色朝上的骰子的个数，求出 $A$ 的取值范围，继而也可以求出 $B$ 的取值范围，判断 $A,B$，是否在取值范围内即可。

#### $A$ 的取值范围

- 红色朝上的骰子的个数为 $0$：

显然 $A$ 只能为 $0$。

- 红色朝上的骰子的个数为 $1$：

$A$ 只能为 $1,4$。

- 红色朝上的骰子的个数为 $2$：

$A$ 可以为 $1+1,1+4,4+4$，既 $A$ 可以为 $2,5,8$。

- 红色朝上的骰子的个数为 $3$：

$A$ 可以为 $1+1+1,1+1+4,1+4+4,4+4+4$，既 $A$ 可以为 $3,6,9,12$。

#### $B$ 的取值范围

- 黑色朝上的骰子的个数为 $0$：

显然 $B$ 也只能为 $0$。

- 黑色朝上的骰子的个数为 $1$：

$B$ 可为 $2,3,5,6$。

- 黑色朝上的骰子的个数为 $2$：

枚举可得 $4\le b\le 12$。

- 黑色朝上的骰子的个数为 $3$：

枚举可得 $6\le b \le 18$。

### 代码

```cpp
#include<bits/stdc++.h>
int a,b;
int main(){
	scanf("%d%d",&a,&b);
	if(a==0){
		if(6<=b&&b<=18) printf("Yes");
		else printf("No");
	}
	else if(a==1||a==4){
		if(4<=b&&b<=12) printf("Yes");
		else printf("No");
	}
	else if(a==2||a==5||a==8){
		if(2<=b&&b<=6&&b!=4) printf("Yes");
		else printf("No");
	}
	else if(a==3||a==6||a==9||a==12){
		if(b==0) printf("Yes");
		else printf("No");
	}
	else printf("No");
	return 0;
}
```


---

## 作者：_ImposterX_ (赞：1)

### 题目描述

[Luogu](https://www.luogu.com.cn/problem/P9564)

### 思路讲解

注意到 $A,B$ 的范围较小，直接打暴力。我们只需要分别三个循环枚举哪些骰子是红色面朝上，另外三个循环枚举哪些骰子黑色面朝上。

详细见代码吧。

复杂度是常数级别的。

### 代码+讲解

```cpp
#include <bits/stdc++.h>
#define int long long
#define gt getchar
#define pt putchar

using namespace std;

const int MAXN=1e8+5;

signed main()
{
	int a,b;
	cin>>a>>b;
	for(int i=0;i<=4;i++)
	{
		if(i!=0&&i!=1&&i!=4) continue;
		for(int j=0;j<=4;j++)
		{
			if(j!=0&&j!=1&&j!=4) continue;
			for(int k=0;k<=4;k++)
			{
				if(k!=0&&k!=1&&k!=4) continue;
           //枚举红色面朝上的骰子
           //i,j,k如果是0代表这个骰子不是红色的。
				if(i+j+k==a)
				{
					int s=3;//一共有3个骰子
					if(i) s--;
					if(j) s--;
					if(k) s--;
					for(int ii=0;ii<=6;ii++)
					{
						if(ii!=0&&ii!=2&&ii!=3&&ii!=5&&ii!=6) continue;
						for(int jj=0;jj<=6;jj++)
						{
							if(jj!=0&&jj!=2&&jj!=3&&jj!=5&&jj!=6) continue;
							for(int kk=0;kk<=6;kk++)
							{
								if(kk!=0&&kk!=2&&kk!=3&&kk!=5&&kk!=6) continue;
								if(ii+jj+kk==b)
								{
                         //ii,jj,kk原理同上
          						 //枚举红色面朝上的骰子
        					    //i,j,k如果是0代表这个骰子不是红色的。
									int ss=s;//不破坏s的值
									if(ii) ss--;
									if(jj) ss--;
									if(kk) ss--;
									if(ss==0)
									{
                           //如果3个骰子正好用光
										cout<<"Yes\n";
										return 0;
									}
								}
								
							}
						}
					}
				}
			}
		}
	}
	cout<<"No";
	return 0;
}
```

---

## 作者：封禁用户 (赞：1)

#### 分析

我们将每个筛子可能筛出的数。

显而易见，第一种情况可以筛出：$0$、$1$、$0$、$0$、$4$、$0$、$0$。
第二种情况能筛出：$0$、$0$、$2$、$3$、$0$、$5$、$6$。

我们可以用一个三重循环来枚举第一种和第二种是否相等，相等就是合法的。


#### 代码

```
for (int i = 1; i <= 6; i++) {
    for (int j = 1; j <= 6; j++) {
		for (int k = 1; k <= 6; k++) {
			if (dy[i] + dy[j] + dy[k] == x && dr[i] + dr[j] + dr[k] == y) {
        	  	 	puts("Yes");
        	  	 	return 0;
       	 		}
		}
	}
```

---

## 作者：One_JuRuo (赞：1)

## 思路

大概是这场比赛最水的题目？

一共只有三个骰子，每个骰子有 $6$ 面，所以总共是 $6^3=216$ 种情况，不用多说，直接暴力。

就是判断是红色还是黑色有点麻烦，可以数组存，写出来代码稍微好看些。

## AC 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int a,b;
int col[7]={0,0,1,1,0,1,1};//各个数字的颜色
int main()
{
	scanf("%d%d",&a,&b);
	for(int i=1;i<=6;++i)
	{
		for(int j=1;j<=6;++j)
		{
			for(int k=1;k<=6;++k)
			{
				int res[2]={0,0};
				res[col[i]]+=i,res[col[j]]+=j,res[col[k]]+=k;//三个骰子加对应颜色
				if(a==res[0]&&b==res[1]) printf("Yes"),exit(0);//判断是否符合条件
			}
		}
	}
	printf("No");//都不符合条件
}
```

---

## 作者：Syncc (赞：0)

## P9564 [SDCPC2023] I-Three Dice 题解

这道题思路比较简单，暴力三重循环枚举，再用两个变量统计红点数和黑点数就行了（不会有人不知道 $1$ 和 $4$ 是红点，其他数字是黑点吧）
### 代码
~~（我知道上面的解释没人看）~~
```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int main(){
	int a,b;
	cin>>a>>b;
	for(int i=1;i<=6;i++){
		for(int j=1;j<=6;j++){
			for(int k=1;k<=6;k++){
				int l=0,r=0;// l为红点数的总点数，r为黑点数的总点数
				if(i==1 || i==4){// 统计
					l+=i;
				}
				
				if(j==1 || j==4){
					l+=j;
				}
				
				if(k==1 || k==4){
					l+=k;
				}
				
				if(i==2 || i==3 || i==5 || i==6){
					r+=i;
				}
				
				if(j==2 || j==3 || j==5 || j==6){
					r+=j;
				}
				
				if(k==2 || k==3 || k==5 || k==6){
					r+=k;
				}
				if(l==a && r==b){
					cout<<"Yes";
					return 0;
				}
			}
		}
	}
	cout<<"No";
	return 0;
}
```


---

## 作者：CheZiHe929 (赞：0)

## 原题链接

[P9564 [SDCPC2023] I-Three Dice](https://www.luogu.com.cn/problem/P9564)

## 简要思路

数据范围很小，直接暴力枚举。

枚举每个点数向上的次数，最后判断合不合法。

判断合法的三个条件：

1. 向上的面中 $1$ 和 $4$ 的和等于输入的 $A$。

2. 向上的面中 $2$ 和 $3$ 和 $5$ 和 $6$ 的和等于输入的 $B$。

3. 所有的点数向上的次数和为 $3$（因为只有三个骰子）。

## 完整代码

```cpp
#include<bits/stdc++.h>
#define int long long
#define endl '\n'
using namespace std;

int A,B;
int num1,num2,num3,num4,num5,num6;//num1 ~ num6 分别代表向上的点数为 1 ~ 6 的次数

signed main(){
	cin>>A>>B;

	for(num1=0;num1<=3;num1++)
		for(num2=0;num2<=3;num2++)
			for(num3=0;num3<=3;num3++)
				for(num4=0;num4<=3;num4++)
					for(num5=0;num5<=3;num5++)
						for(num6=0;num6<=3;num6++){//枚举每个点数向上的次数
							
							if(A==num1*1+num4*4 && B==num2*2+num3*3+num5*5+num6*6){//满足输入的数据

								if(num1+num2+num3+num4+num5+num6==3){//保证合法（是三个骰子）
							    	cout<<"Yes"<<endl;
									return 0;
								}
								
							}
						}
						
	cout<<"No"<<endl;//一直没有满足输入的答案

	return 0;
}
```

## AC 记录

[This](https://www.luogu.com.cn/record/121666532).

**THE END.**

**THANK YOU.**

---

## 作者：InversionShadow (赞：0)

暴力即可。

三重循坏枚举每个骰子的点数，然后根据题目所给的红黑点累加即可。

```cpp
#include <bits/stdc++.h>

using namespace std;

int a, b;

int main() {
  cin >> a >> b;
  for (int i = 1; i <= 6; i++) { // 6 种情况
    for (int j = 1; j <= 6; j++) {
      for (int k = 1; k <= 6; k++) {
        int sum = 0, ans = 0;
        if (i == 1 || i == 4) sum += i; 
        if (j == 1 || j == 4) sum += j;
        if (k == 1 || k == 4) sum += k; // 以上都为红点
        if (i != 1 && i != 4) ans += i; // 以下都为黑点
        if (j != 1 && j != 4) ans += j;
        if (k != 1 && k != 4) ans += k;
        if (sum == a && ans == b) {
          cout << "Yes";
          return 0;
        } 
      }
    }
  }
  cout << "No"; 
  return 0;
}
```

---

## 作者：1qaz234567pzy (赞：0)

水题一道。


------------

直接暴力枚举每一个骰子的朝上的面的数字的情况，然后对每一种情况分别判断是否满足就可以了，满足就输出 `Yes`，对每一种情况都处理完后如果还没输出过 `Yes` 的话，就输出 `No`。由于总共有三个骰子，只有 $6^3 = 216$ 种情况，快的飞起。

```cpp
#include<bits/stdc++.h>
using namespace std;
int a,b;
int A,B;
int  main()
{
	cin>>b>>a;
	for(int qqq=1;qqq<=6;qqq++)
	{
		for(int www=1;www<=6;www++)
		{
			for(int eee=1;eee<=6;eee++)
			{
				A=0;
				B=0;
				if(qqq==1||qqq==4)
				{
					B+=qqq;
				}
				else
				{
					A+=qqq;
				}
				
				if(www==1||www==4)
				{
					B+=www;
				}		
				else
				{
					A+=www;
				}		
				
				if(eee==1||eee==4)
				{
					B+=eee;
				}
				else
				{
					A+=eee;
				}
				
				if(A==a&&B==b)
				{
					cout<<"Yes"<<endl;
					return 0;
				}
			}
		}
	}
	cout<<"No";
	return 0;
}

```


---

## 作者：Hog_Dawa_IOI (赞：0)

直接暴力三重循环。      
枚举三个骰子朝上那面的点数，然后统计红色点和黑色点的数量，再判断是否符合规定。
```cpp
#include<stdio.h>
int main()
{
    int s1,s2;
    scanf("%d%d",&s1,&s2);
    for(int a=1;a<=6;a++) for(int b=1;b<=6;b++) for(int c=1;c<=6;c++)
    {
        int red=0,black=0;
        if(a==1||a==4) red+=a;
        else black+=a;
        if(b==1||b==4) red+=b;
        else black+=b;
        if(c==1||c==4) red+=c;
        else black+=c;
        if(red==s1&&black==s2) {printf("Yes");return 0;}
    }
    printf("No");
}
```

---

## 作者：SakurajiamaMai (赞：0)

由于骰子数量为 $3$，直接暴力求出所有的情况然后一一判断即可。分以下几种情况：

红面为 $0$，红面为 $1$，红面为 $2$，以及红面为 $3$，黑面与之对应，一一判断即可。

```cpp
#include <bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e6+10,mod=1e9+7;
string s;
int n,t,a[N],f[N],res,num,ans,m,k;
bool vis[N];
void solve()
{  
    while(cin>>n>>m){
    if(n==0&&(m==6||m==10||m==11||m==14||m==9||m==15||m==18||m==7||m==8||m==16||m==17||m==12||m==13)) cout<<"Yes"<<endl;
    else if((n==1||n==4)&&(m==5||m==7||m==8||m==9||m==11||m==4||m==6||m==10||m==12)) cout<<"Yes"<<endl;
    else if((n==2||n==5||n==8)&&(m==2||m==3||m==5||m==6)) cout<<"Yes"<<endl;
    else if((n==3||n==12||n==9||n==6)&&m==0) cout<<"Yes"<<endl;
    else cout<<"No"<<endl;
    }
}
signed main()
{
    std::ios::sync_with_stdio(false),cin.tie(0),cout.tie(0);
    solve();
    return 0;
}

```


---

## 作者：xiaoyang111 (赞：0)

# P9564 [SDCPC2023] I-Three Dice 题解

## 前言

[题目传送门。](https://www.luogu.com.cn/problem/P9564)

[可能更好的阅读体验。](https://www.luogu.com.cn/blog/xiaoyang111/solution-p9564)

## 讲解

### 思路

此题涉及到的算法有枚举和模拟，具体解题步骤见下。

1. 三重循环遍历每个骰子的点数。

2. 按照题目中的要求，分别算出红色点数和黑色点数的点数和。

3. 判断当前方案的红色的点数之和是否恰好为 $A$，当前方案的黑色的点数之和是否恰好为 $B$，如果符合，按照题意输出。

4. 如果枚举结束没有一种符合条件的方案，按照题意输出。

时间复杂度极低，可以通过此题。

### 代码

下面是我的~~高清无注释~~代码，可能风格有点丑，请见谅。

```cpp
#include <iostream>
using namespace std;
int main(){
	int a,b;
	cin >> a >> b;
	for (int i=1;i<=6;++i){
		for (int j=1;j<=6;++j){
			for (int k=1;k<=6;++k){
				int sm1=0,sm2=0;
				if (i==1 || i==4){
					sm1+=i;
				}else{
					sm2+=i;
				}
				if (j==1 || j==4){
					sm1+=j;
				}else{
					sm2+=j;
				}
				if (k==1 || k==4){
					sm1+=k;
				}else{
					sm2+=k;
				}
				if (sm1==a && sm2==b){
					cout<<"Yes\n";
					return 0;
				}
			}
		}
	} 
	cout<<"No\n";
	return 0;
}
```

---

## 作者：yanxiashi (赞：0)

对于一个骰子，一和四为红，其他为黑，本题只需暴力分别枚举红色面朝上和黑色面朝上的情况即可。

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
int a,b,n = 6;
int main() {
  cin >> a >> b;
  for(int i = 1;i <= n;i++){
    for(int j = 1;j <= n;j++){
     for(int k = 1;k <= n;k++){
      int sum = 0, ans = 0;
      if(i != 1 && i != 4) ans += i; 
      if(j != 1 && j != 4) ans += j;
      if(k != 1 && k != 4) ans += k;      
      if(i == 1 || i == 4) sum += i; 
      if(j == 1 || j == 4) sum += j;
      if(k == 1 || k == 4) sum += k;
      if(sum == a && ans == b){
        cout << "Yes" << endl;
        return 0;
      } 
    }
  }
  cout << "No" << endl; 
  return 0;
}
```


---

## 作者：__Tonycyt__ (赞：0)

### 思路
这题可以先枚举一遍可行的方案，然后打出表，放进去就 AC 了。  
主要看代码实现。
### 实现
#### 打表代码如下：
```cpp
#include<bits/stdc++.h>
using namespace std;
bool vis[20][20];//是否被访问过
int main(){
	int sum_color[2];//两种颜色分别的点数之和
	bool num_color[7]={0,0,0,1,0,0,1};//不同点数对应的颜色（红是0，蓝是1）
	for(int i=1;i<=6;i++)
		for(int j=1;j<=6;j++)
			for(int k=1;k<=6;k++){//逐个枚举三个骰子
				sum_color[0]=sum_color[1]=0;
				sum_color[num_color[i]]+=i;
				sum_color[num_color[j]]+=j;
				sum_color[num_color[k]]+=k;
				vis[sum_color[0]][sum_color[1]]=1;//记录可行方案 
			}
	/*接下来就是输出，不做注释*/
	cout<<"bool can[20][20]={\n";
	for(int i=0;i<20;i++){
		cout<<"{";
		for(int j=0;j<20;j++){
			cout<<vis[i][j];
			if(j!=19) cout<<",";
		}
		cout<<"},\n";
	}
	cout<<"}";
	return 0;
}
```
我们得到了一份输出：
```
bool can[20][20]={
{0,0,0,0,0,0,0,0,0,1,0,0,1,0,0,1,0,0,1,0},
{0,0,0,0,0,0,1,0,0,1,0,0,1,0,0,0,0,0,0,0},
{0,0,0,1,0,0,1,0,0,1,0,0,1,0,0,0,0,0,0,0},
{1,0,0,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0},
{1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,0,0,0,0,0},
{1,0,0,1,0,0,1,0,0,1,0,0,1,0,0,0,0,0,0,0},
{1,0,0,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0},
{1,0,0,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0},
{1,0,0,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0},
{1,0,0,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0},
{1,0,0,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0},
{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
}
```
把这个输出直接嵌套在代码里面即可。

### AC 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
bool can[20][20]={//打表 
{0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,0},
{0,0,0,0,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0},
{0,0,1,1,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0},
{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0},
{0,0,1,1,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0},
{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,1,1,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0},
{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
};
int main(){
	int n,m;
	cin>>n>>m;//输入 
	if(can[n][m]) cout<<"Yes";//输出 
	else cout<<"No";
	return 0;
}

```
### 管理员大大辛苦了，希望能过。
无耻的求个赞。

---

