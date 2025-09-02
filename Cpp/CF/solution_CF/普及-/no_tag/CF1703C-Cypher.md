# Cypher

## 题目描述

有一把 $n$ 个锁轮的锁，每个锁轮上写有数字 $a_i$ ，对于第 $i$ 个锁轮，做了 $b_i$ 次操作。这些操作有两种类型：

- `U`：锁轮上的数字 $+1$ ，超过 $9$ 则变为 $0$ 。
- `D`：锁轮上的数字 $-1$ ，小于 $0$ 则变为 $9$ 。

现在给定操作后的锁轮和操作，请你还原操作前的锁轮。

## 说明/提示

$1 \le n,t \le 100,0 \le a_i \le 9,1 \le b_i \le 10$

## 样例 #1

### 输入

```
3
3
9 3 1
3 DDD
4 UDUU
2 DU
2
0 9
9 DDDDDDDDD
9 UUUUUUUUU
5
0 5 9 8 3
10 UUUUUUUUUU
3 UUD
8 UUDUUDDD
10 UUDUUDUDDU
4 UUUU```

### 输出

```
2 1 1 
9 0 
0 4 9 6 9```

# 题解

## 作者：X____ (赞：10)

### 题目大意
给一个经过许多次操作的密码锁，
给出具体操作，要求还原这个锁。
其中 U 代表向上一个数， D 代表向下拨一个数。
### 思路
因为给出的锁是最终状态的锁，所以操作是反向的，也就是说 U 代表减 1， D 代表加 1。
所以从后往前推即可。
### 代码
```c
#include<cstdio>
#include<iostream>
#include<iomanip>
#include<cstring>
#include<string>
using namespace std;
int a[101];
char c; 
int main()
{
	int t,n,len; 
	cin>>t;
	while(t--)
	{
		cin>>n;
		for(int i=1;i<=n;i++)
		{
			cin>>a[i];//记录锁的最终状态 
		}
		for(int i=1;i<=n;i++)
		{
		   cin>>len;
		   while(len--)
		   {
		   	cin>>c;//记录每次操作 
		   	if(c=='D')//如果是 D 就加，是 U 就减 
		   	{
		   		a[i]++;
		   		if(a[i]==10) a[i]=0;
			   }//如果是 10 就换成 0 
			 else if(c=='U')
			 {
			 	a[i]--;
			 	if(a[i]==-1) a[i]=9;
			   } //是 -1 就换成 9 
			   }	
		}
		for(int i=1;i<=n;i++)
		cout<<a[i]<<" ";
		cout<<endl;
	}
	return 0;
}
```




---

## 作者：zhicheng (赞：2)

### 题意简述

给定一个锁的最终状态和达到状态所进行的操作，求出锁的初始状态。

### 思路

按照题目要求模拟即可。

有几个需要注意的点：

* 题目要求我们还原状态，说明我们需要反着进行题目给出的序列：加变减，减变加。因为操作互相独立，所以操作的顺序没有影响，不用从后往前。

* 如果到了 $9$ 还要加，应该变成 $0$。同理，如果到了 $0$ 还要减，应该变成 $9$。

### Code

```cpp
#include<bits/stdc++.h>
using namespace std;
int p[110];
int main(){
	int n,a,u;
	char c;
	scanf("%d",&n);
	while(n--){
		scanf("%d",&a);
		for(int i=1;i<=a;i++){
			scanf("%d",&p[i]);
		}
		for(int i=1;i<=a;i++){
			scanf("%d ",&u);
			while(u--){
				scanf("%c",&c);
				if(c=='U'){
					p[i]--;  //操作反向，加变减
					if(p[i]==-1){  //注意下界
						p[i]=9;
					}
				}
				else{
					p[i]++;
					if(p[i]==10){  //注意上界
						p[i]=0;
					}
				}
			}
		}
		for(int i=1;i<=a;i++){
			printf("%d ",p[i]);
		}
		printf("\n");
	}
}
```

---

## 作者：shenyiran (赞：1)

### 题意
给你密码最终状态和操作的过程，求出密码的初始状态。
### 思路
读入后，将每个转动的过程倒退回去，但转回去时和转动的过程是相反的，并且这里还要注意 $0$ 和 $9$ 是**相连**的，模拟完输出答案即可。
### AC CODE
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,a[120],b;
char s;
int main(){
	cin>>t;
	while(t--){
		scanf("%d",&n);
		for(int i=1;i<=n;i++){
			cin>>a[i];
		}
		for(int i=1;i<=n;i++){
			cin>>b;
			for(int j=0;j<b;j++){//模拟
				cin>>s;
				if(s=='U'){
					a[i]--;
					if(a[i]==-1){//判断有没有超范围
						a[i]=9;//
					}
				}
				else if(s=='D'){
					a[i]++;
					if(a[i]==10){
						a[i]=0;//
					}
				}
			}
		}
		for(int i=1;i<=n;i++){
			printf("%d ",a[i]);
		}
		printf("\n");
	}
	return 0;
}
```
### 后记
~~没看到数据范围调了半小时~~

---

## 作者：mzyc_yang2021 (赞：1)

题意：给你一堆经过很多操作后的字符串，让你将其还原。

思路：题目共有两种操作，要么把这一位向上拨，要么向下拨。因为我们要还原字符串，所以我们只需要做相反操作即可（即题目向上，我们就向下，题目向上我们就向下）。

注意：因为是在拨锁，所以，若是向上来到 $0$ ，则还原后就是 $9$ 。若向下来到 $9$ ，就向上还原到 $0$ 。

代码（加解释）：
```cpp
#include<bits/stdc++.h>
using namespace std;
int t,n,pw[200];
int main()
{
	cin>>t;
	while(t--)
	{
		memset(pw,-1,sizeof(pw)); // 清空密码数组
		cin>>n;
		for(int i=1;i<=n;i++) cin>>pw[i];
		for(int i=1;i<=n;i++)
		{
			int a;
			char b;
			cin>>a;
			for(int j=1;j<=a;j++)
			{
				cin>>b;
				if(b=='U') // 若向上，就向下把它还原
					if(pw[i]==0) pw[i]=9; // 判断注意情况
					else pw[i]--;
				else // 若向下，反之
					if(pw[i]==9) pw[i]=0; // 注意情况
					else pw[i]++;
			}
		}
		for(int i=1;i<=n;i++) cout<<pw[i]<<" "; // 输出还原后的每一位
		cout<<endl;
	}
	return 0;
}
```

---

## 作者：ZZQF5677 (赞：0)

### 解题思路
这题可以模拟，那么我们就对每一位倒推，如果输入`U`（向上）我们就像下拨，如果输入`D`（向下）我们就像上。但是还要注意 $0$ 往下是 $9$，$9$ 往上是 $0$。

### 代码
```cpp
#include <bits/stdc++.h>
using namespace std;
int t, n, a[123], l;
string s;
int main() {
  cin >> t;
  while (t--) {
    cin >> n;
    for (int i = 1; i <= n; i++) {
      cin >> a[i];
    }
    for (int i = 1; i <= n; i++) {
      cin >> l >> s;
      for (int j = 0; j < s.size(); j++) {
        if (s[j] == 'U') {
          a[i]--;
          if (a[i] < 0) {
            a[i] = 9;
          }
        } else {
          a[i]++;
          if (a[i] > 9) {
            a[i] = 0;
          }
        }
      }
    }
    for (int i = 1; i <= n; i++) {
      cout << a[i] << " ";
    }
    puts("");
  }
  return 0;
}
```

---

## 作者：sandwave114514 (赞：0)

[传送门](https://www.luogu.com.cn/problem/CF1703C)

题目大意

给定一个长度为 $n$ 的密码锁、操作第 $i$ 位上的操作次数   $a_i$ ，操作共两种，$U$ 与 $D$ 。$U$ 操作将会把当前的值加 $1$，如果值为 $9$，则会变成 $0$ 。$D$ 操作将会把当前的值减 $1$，如果值为 $0$，则会变成 $9$ ，求操作前的密码锁序列。

解题思路

很明显，我们按照题意一个一个的倒推即可，注意，操作会反过来。

代码如下

```cpp
#include<bits/stdc++.h> //万能头 
using namespace std;
long long read(){
	long long x=0,sgn=1;char ch=getchar();
	while(ch<'0'||ch>'9'){if(ch=='-')sgn=-1;ch=getchar();}
	while(ch>='0'&&ch<='9'){x=(x<<3)+(x<<1)+(ch&15);ch=getchar();}
	return x*sgn;
}//快读 
long long t,n,a[100010],len;
string st;
int main(){
	t=read();
	while(t--){
		n=read();
		for(int i=1;i<=n;i++)a[i]=read();
		for(int i=1;i<=n;i++){
			len=read();
			cin>>st;
			for(int j=0;j<len;j++){
				if(st[j]=='D'){//逐个字符判断 
					if(a[i]==9)a[i]=0;
					else a[i]++; 
				}
				else{
					if(a[i]==0)a[i]=9;
					else a[i]--;
				}
			}
		}
		for(int i=1;i<=n;i++)cout<<a[i]<<" ";
		cout<<endl;
	}
    return 0;//完结撒花 
}

```


---

## 作者：正负君 (赞：0)


# CF1703C Cypher 题解

## 思路

这道题也是非常的简单，但坑点是比较多的，需要仔细观察。  

主要是在计算轮数的时候需要注意以下几点：  

- 我们不需要一开始就把初始轮数存储上，而是先置为 $0$，先操作，最后再将轮数加上。

- 当字符为 $\texttt{D}$ 时，轮数应该 $+1$；反之，当字符为 $\texttt{U}$ 时，轮数应 $-1$。

- 我们还需要考虑轮数是否 $\ge0$ 且 $\le9$，保证轮数在正常范围内。如果未在正常范围内，我们将经过一些操作将其置为正常范围，分两种情况：  
     - 第一种情况（轮数 $>9$）：  
     我们直接将轮数设为轮数 $\bmod10$。
     - 第二种情况（轮数 $<0$）：  
     我们将轮数设为 $10-$ 轮数的相反数 $\bmod 10$；  
     
     注：我们考虑到第二种情况操作完成后还有可能是 $10$，所以我们将轮数设为轮数 $\bmod10$。

## 代码

```cpp
#include<iostream>
using namespace std;
int t,n;
int main()
{
  cin>>t;
  while(t--)
  {
    char temp;
    cin>>n;
    int a[n+1],b[n+1];
    for(int i=1; i<=n; i++)
    {
      cin>>a[i];
    }
    for(int i=1; i<=n; i++)
    {
      int wheel=0;
      cin>>b[i];
      for(int j=1; j<=b[i]; j++)
      {
        cin>>temp;
        if(temp=='D')
        {
          wheel++;
        }
        else
        {
          wheel--;
        }
      }
      wheel+=a[i];
      if(wheel>=0)   //这里和我说的两种情况判断条件不一样，但是本质还是一样的。
      {
        wheel%=10;
      }
      else
      {
        wheel=10-(-wheel)%10;
      }
      wheel%=10;
      cout<<wheel<<' ';
    }
    cout<<endl;
  }
  return 0;
}
```

---

## 作者：hanzhang666 (赞：0)

# 题面翻译
给定密码锁的最终状态和所进行的操作，求初始状态。    
本题有多组数据。
# 分析
我们考虑倒推，注意一下几点：

- 倒推 ```U``` 向下，```D``` 向上。
- $0$ 的下方是 $9$，$9$ 的上方是 $0$。

# Code
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
	int x=0,f=1;
	char c=getchar();
	while(c<'0'||c>'9'){
		if(c=='-')f=-1;
		c=getchar();
	}
	while(c>='0'&&c<='9'){
		x=x*10+c-'0';
		c=getchar();
	}
	return x*f;
}
int a[105];
int cnt;
signed main(){
	int T=read();
	while(T--){
		int n=read();
		for(int z=1;z<=n;z++){
			a[z]=read();
		}
		for(int z=1;z<=n;z++){
			cnt=0;
			int m=read();
			for(int i=1;i<=m;i++){
				char c=getchar();
				if(c=='U'){//U向下 
					cnt-=1;
				}
				else cnt+=1;//D向上 
			}
			cnt%=10;
			a[z]+=cnt;
			if(a[z]>=10) a[z]%=10;
			if(a[z]<0){
				a[z]+=10;
			}
		}
		for(int z=1;z<=n;z++){
			cout<<a[z]<<" ";
		}
		cout<<endl;
	}
}
```


---

## 作者：OLE_OIer (赞：0)

## CF1703C Editorial

这道题是一道经典的字符串模拟题。

思路：对于每一个密码锁中的特定一位可看做是独立的。于是统计向上几次向下几次然后操作即可。

附上代码：注意负数在取模的时候与正数不同，要先把它化成正数。

```cpp
//CF1703C Cypher
#include<bits/stdc++.h>
#define int long long
#define elif else if
using namespace std;
void func(){
	int n;cin>>n;
	int a[110]={};char c;//由于只需统计个数，所以不需要开字符数组
	for(int i=1;i<=n;++i) cin>>a[i];
	for(int i=1;i<=n;++i){
		int len;cin>>len;
		int u=0,d=0;
		for(int j=1;j<=len;++j){
			cin>>c;
			if(c=='U') ++u;//统计
			else ++d;
		}
		a[i]=(a[i]+(d-u)+10)%10;//化为正数后取模
	}
	for(int i=1;i<=n;++i) cout<<a[i]<<" ";
	cout<<"\n";
}
signed main(){
	ios::sync_with_stdio(false);
	int n;cin>>n;
	for(int i=1;i<=n;++i) func();
	return 0;
}
```

---

## 作者：sunkuangzheng (赞：0)

## 简要题意
给定一把锁经过若干次操作后的状态和具体操作，要求还原操作之前的状态。
## 题目分析
因为给的是最终状态，所以操作反向的，遇到 `U` 要 $-1$ ，遇到 `D` 要 $+1$ ，但是要注意如果出现 `U` 且当前锁的数字是 $0$ 要变成 $9$ ，同理如果出现 `D` 且当前锁的数字是 $9$ 要变成 $0$ 。由于锁的数字加减先后顺序不影响答案，所以不需要由后向前操作。
## 完整代码
```cpp
#include <iostream>
using namespace std;
int main(){
    int t,n,a[105] = {0},x;//t是数据组数，n是锁的位数，a数组记录锁上的数字，x是一次操作的字符个数
    char p;//p存储字符'U'或'D'
    cin >> t;
    for(int i = 1;i <= t;i ++){
        cin >> n;
        for(int j = 1;j <= n;j ++){
            cin >> a[j];
        }
        for(int j = 1;j <= n;j ++){
            cin >> x;
            for(int k = 1;k <= x;k ++){
                cin >> p;
                if(p == 'U'){
                    if(a[j] != 0){
                        a[j] --;
                    }
                    else{
                        a[j] = 9;
                    }
                }
                else if(p == 'D'){
                    if(a[j] != 9){
                        a[j] ++;
                    }
                    else{
                        a[j] = 0;
                    }
                }
            }
        }
        for(int j = 1;j <= n;j ++){
            cout << a[j] << " ";
        }
        cout << "\n";
    }
}
```

---

## 作者：thh_loser (赞：0)

# CF1703C Cypher 题解

## 题目描述

给出一个密码锁的最终状态以及操作过程，求锁的初始状态。

## 思路

按照题目要求模拟即可（需要注意由于是倒推，给出的加要变成减，减要变成加）。

### code

```
#include<bits/stdc++.h>
using namespace std;
int t,n,a[110],cd;
char s;
int main(){
	scanf("%d",&t);
	while(t--){
		scanf("%d",&n);
		for(int i=0;i<n;i++){
			cin>>a[i];
		}
		for(int i=0;i<n;i++){
			cin>>cd;
			for(int j=0;j<cd;j++){
				cin>>s;
				if(s=='D'){
					a[i]++;//减变加 
				}
				else{
					a[i]--;//加变减 
				}
				if(a[i]<0){
					a[i]+=10;
				}//下界 
				else if(a[i]>9){
					a[i]-=10;
				}//上界 
			}
		}
		for(int i=0;i<n;i++){
			cout<<a[i]<<" ";
		}
		cout<<"\n";
	}
	return 0;
}
```

---

## 作者：NATO (赞：0)

### 题意简述：
给定一个长度为 $n$ 的密码锁、操作第 $i$ 位上的操作次数 $a_i$，操作共两种，$U$ 与 $D$。$U$ 操作将会把当前的值加 $1$，如果值为 $9$，则会变成 $0$。$D$ 操作将会把当前的值减 $1$，如果值为 $0$，则会变成 $9$，求：操作前的密码锁序列。

### 解题分析：
很明显，我们需要将 $U$ 与 $D$ 操作反过来使用，逆推规则如下：

对于操作 $U$，倒推时将当前的值减 $1$，如果值为 $0$，就会变成 $9$；

对于操作 $D$，倒推时把当前的值加 $1$，如果值为 $9$，就会变成 $0$。

按照此规则判断边际，一个一个倒退即可。

#### 参考代码：
```cpp
#include<bits/stdc++.h> 
#define ll long long
using namespace std;
ll t,n,a[105],k;
char cd;
int main()
{
	ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin>>t;
	while(t--)
	{
		cin>>n;
		for(ll i=1;i<=n;++i)
			cin>>a[i];
		for(ll i=1;i<=n;++i)
		{
			cin>>k;
			for(ll j=1;j<=k;++j)
			{
				cin>>cd;
				if(cd=='U')
				{
					if(a[i]==0)
						a[i]=9;
					else
						--a[i];
				}
				else
				{
					if(a[i]==9)
						a[i]=0;
					else
						++a[i];
				}
			}
		}
		for(ll i=1;i<=n;++i)
			cout<<a[i]<<' ';cout<<'\n';
	}
}
```


---

## 作者：xiaomuyun (赞：0)

[题目传送门](https://www.luogu.com.cn/problem/CF1703C)

## 题目分析

因为我们要还原答案，所以说题目说的 `D` 实际上是要我们上升，而 `U` 是下降。所以可以直接对于锁上每个位置的操作全部“取反”，碰到一个 `D` 就反过来让锁上的数 $+1$，碰到一个 `U` 就让锁上的数 $-1$ 即可。只需要注意 $9+1$ 会变成 $0$，$0-1$ 会变成 $9$ 就行了，代码难度不大。

## 代码实现

```cpp
#include<iostream>
#include<string>
#include<cstdio>
using namespace std;
int t,n,a[101];
int main(){
	scanf("%d",&t);
	while(t--){
		scanf("%d",&n);
		for(int i=1;i<=n;++i) scanf("%d",&a[i]);
		for(int i=1,k;i<=n;++i){
			string s;
			scanf("%d",&k);
			cin>>s;
			for(int j=0;j<s.length();++j){
				if(s[j]=='D'){
					if(a[i]==9) a[i]=0;//特判
					else ++a[i];
				} else {
					if(!a[i]) a[i]=9;
					else --a[i];
				}
			}
		}
		for(int i=1;i<=n;++i) printf("%d ",a[i]);
		putchar('\n');
	}
	return 0;
}
```

---

## 作者：tian_jun_cheng (赞：0)

## 题意描述

给你 $n$ 个滚轮，从 $0$ 到 $9$ 标号，对每个滚轮进行操作，首尾相连。

## 思路

还是模拟题，注意判断首尾相连的情况，不会超时。

注意是逆序操作，题目中要还原原来的滚轮。

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[101];
int main()
{
	int t;
	cin>>t;
	while(t--)
	{
		int n;
		cin>>n;
		for(int i=1;i<=n;i++)
			cin>>a[i];
		string s;
		for(int i=1;i<=n;i++)
		{
			int k;
			cin>>k>>s;
			for(int j=0;s[j];j++)
			{
				if(s[j]=='D')
				{
					a[i]++;
					if(a[i]==10)
						a[i]=0;
				}
				else
				{
					a[i]--;
					if(a[i]==-1)
						a[i]=9;
				}
			}
		}
		for(int i=1;i<=n;i++)
			cout<<a[i]<<" ";
		cout<<endl;
	}
	return 0;
}
```


---

## 作者：Halberd_Cease (赞：0)

## 题目大意

有一个密码锁，共 $n$ 位，给出其旋转后的状态，以及对于每一个密码位的操作，求该密码锁初始状态。

其中，操作共分 $2$ 种：

- ```U``` 表示将该密码位往上调一位，如从 ```3``` 变为 ```4```，从 ```9``` 变为 ```0```。

- ```D``` 表示将该密码位往下调一位，如从 ```4``` 变为 ```3```，从 ```0``` 变为 ```9```。

## 分析
对于每一个密码位，模拟即可，注意我们是从旋转后推初始值，因此所有操作都要反着做。

注意边界，```9``` 上面是 ```0```。

## Code：
```cpp
#include<bits/stdc++.h>
using namespace std;
int a[110];
void up(int num)
{
	a[num]--;
	if(a[num]==-1)a[num]=9;
}
void down(int num)
{
	a[num]++;
	if(a[num]==10)a[num]=0;
}
int main()
{
	int t;
	cin>>t;
	while(t--)
	{
		int n;
		cin>>n;
		for(int i=1;i<=n;i++)
		{
			cin>>a[i];
		}
		for(int i=1;i<=n;i++)
		{
			int b;
			cin>>b;
			char x;
			for(int j=1;j<=b;j++)
			{
				cin>>x;
				if(x=='U')up(i);
				else down(i);
			}
		}
		for(int i=1;i<=n;i++)
		{
			cout<<a[i]<<' ';
		}
		cout<<'\n';
	}
}
```

---

## 作者：Dovish (赞：0)

## 题意：
首先，对于每组数据而言，我们会已知一个密码锁的位数，转动后的数字与会如何转动的。设字母 $D$ 为逆转，但因为是求其初始的值，所以当前数字应该加 $1$；设字母 $U$ 为顺转，但同上，当前数字应该减 $1$。
## 思想：
我们将转动过程转化为：顺转 $ans$ 次（逆转的话 $ans$ 就减一），然后将该数字加上 $ans$ 再判断答案小于 $0$ 与大于 $9$ 的越界情况。（当然，也可以像题意所示，根据所给的转动过程直接一步步修改该数字的值。）
## 代码如下：
```
#include<bits/stdc++.h>
using namespace std;
int a[10001];
int main()
{
	int t,n;
	cin>>t;//外层t组数据
	while(t--)
	{
		cin>>n;
		for(int i=1;i<=n;i++)
		cin>>a[i];//输入
		for(int i=1,ls;i<=n;i++)
		{
			string s;
 			int ans=0;
			cin>>ls>>s;//输入转动次数与每次转动的顺逆
			for(int j=0;j<s.size();j++)
			if(s[j]=='D')ans++;//是顺转，答案加一
			else ans--;//否则是逆转，答案减一
			cout<<(a[i]+ans+20)%10<<" ";
 			/*因为字符串长度不会超过10，所以可以将
			答案加上20（处理负值）再对10取余（处理
			大于9的值）的方式来处理越界的情况*/
		}
		cout<<endl;
	}
	return 0;
}
```

---

## 作者：Simclover (赞：0)

题意：打乱一个密码锁，给你打乱后的密码锁上的各个数字以及打乱密码锁的操作，其中 $U$ 表示上，$D$ 表示下，求这个密码锁的初始序列。

我们可以按照题意去模拟，把 $U$ 和 $D$ 反过来即可，要注意 $0$ 与 $9$ 的特判。

代码：

```cpp
#include<cstdio>
#include<iostream>
#include<string>
#include<cstring>

using namespace std;

int t;
int a[1000010];
string s;
int n;
int n1;
bool vis[1010];

int main(){
    scanf("%d",&t);
    while(t--){
        scanf("%d",&n);
        for(int i=1;i<=n;i++){
            scanf("%d",&a[i]);
        }
        for(int i=1;i<=n;i++){
            scanf("%d",&n1);
            cin>>s;
            
            for(int j=0;j<s.length();j++){
                if(s[j]=='U'){
                    a[i]--;
                }
                if(s[j]=='D'){
                    a[i]++;
                }
                if(a[i]==10) a[i]=0;//特判
                if(a[i]==-1) a[i]=9;
            }
            
        }
        
		for(int i=1;i<=n;i++){
            printf("%d ",a[i]);
        }
        
        puts("");
    }
    return 0;
}
```


---

## 作者：Scorilon (赞：0)

题意：模拟一个 $n$ 位密码锁。

做法：直接模拟，注意往后推，即若为 $U$ 变为 $D$，若为 $D$ 变为 $U$。注意 $0$ 和 $9$ 进行操作时的特判。

其中 $0-1$ 应为 $9$，$9+1$ 应为 $0$。

```cpp
#include<cstdio>
#include<iostream>
using namespace std;
int s[105];
int t,n;
char a;
int main(){
	scanf("%d",&t);
	while(t--){
		scanf("%d",&n);
		for(int i=1;i<=n;i++){
			scanf("%d",&s[i]);//输入密码锁
		}
		int m;
		for(int i=1;i<=n;i++){
			scanf("%d",&m);
			for(int j=1;j<=m;j++){
				scanf(" %c",&a);
				if(a=='D'){//若为 D 执行 U
					s[i]++;
					if(s[i]==10) s[i]=0;//特判
				}
				else if(a=='U'){//若为 U 执行 D
					s[i]--;
					if(s[i]==-1) s[i]=9;//特判
				}
			}
		}
		for(int i=1;i<=n;i++){
			printf("%d ",s[i]);//输出答案
		}
		printf("\n");
	}
	return 0;
}

```


---

## 作者：Jasper08 (赞：0)

### 【题目分析】

一道小模拟。模拟时要注意以下几点：

- 不用反过来模拟。因为操作顺序不影响最终结果。

- 把 $\texttt{U}$ 操作变为 $\texttt{D}$ 操作，$\texttt{D}$ 操作变为 $\texttt{U}$ 操作。即若输入的字符串是 $\texttt{UDDUD}$，模拟的时候就要变成 $\texttt{DUUDU}$。

- 对 $9$ 进行 $\texttt{U}$ 操作会使其变成 $0$，对 $0$ 进行 $\texttt{D}$ 操作会使其变成 $9$。

```cpp
#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cctype>
#include <iomanip>

using namespace std;

const int N = 110;

int ans[N]; //记录答案

int down(int x) { //模拟D操作
	if (x == 0)
		return 9;
	return x-1;
}

int up(int x) { //模拟U操作
	if (x == 9)
		return 0;
	return x+1;
}

int main() {
	ios::sync_with_stdio(0); //cin,cout加速
	cin.tie(0);
	cout.tie(0);

	int t;
	cin >> t;
	while (t -- ) {
		int n;
		cin >> n;
		for (int i = 1; i <= n; ++i) 
			cin >> ans[i];
		
		for (int i = 1; i <= n; ++i) {
			int m;
			cin >> m;
			string s;
			cin >> s;
			for (int j = 0; j <= m; ++j) { //模拟每次操作
				if (s[j] == 'U') //U操作变为D操作
					ans[i] = down(ans[i]);
				else //D操作变为U操作
					ans[i] = up(ans[i]);
			}
			cout << ans[i] << " ";
		}
		cout << endl;
	}
	return 0;
}
```

---

## 作者：Buried_Dream (赞：0)

## 题意：

给你现在这个密码的状态，告诉你他是怎么转换来的，输出原来的状态。

## Solution

我们对于每一位直接模拟即可。

如果他是向上过来的，我们就把他减 $1$。

当我们减成 $-1$ 的时候，因为他是一个环，所以我们把他再变成 $9$。

如果他是向下过来的，我们就把他加 $1$。

当我们加成 $10$ 的时候，因为他是一个环，所以我们把他再变成 $0$。

```cpp
int a[N];
char ch[N];
void Main() {
	int n = read();
	for(int i = 1; i <= n; i++) a[i] = read();
	for(int i = 1; i <= n; i++) {
		int x = read();
		cin >> (ch + 1);
		for(int j = 1; j <= x; j++) {
			if(ch[j] == 'D') {
				a[i]++; 
				if(a[i] == 10) a[i] = 0;
			}
			else {
				a[i]--;
				if(a[i] == -1) a[i] = 9;
			}
		}
	}
	for(int i = 1; i <= n; i++) cout << a[i] << " ";
	printf("\n");
}

signed main() 
{
	int T = read();
	while(T--) Main();
	return 0;
}
```


---

