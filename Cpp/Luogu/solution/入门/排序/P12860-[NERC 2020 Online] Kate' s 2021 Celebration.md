# [NERC 2020 Online] Kate' s 2021 Celebration

## 题目描述

Kate 的 2020 年并不顺利，因此她很高兴这一年即将结束。她计划以盛大的方式庆祝 2021 新年。

Kate 决定为她的 2021 庆祝购买四个气球，上面分别印有数字 $\texttt{2}$、$\texttt{0}$、$\texttt{2}$、$\texttt{1}$。她访问了一家商店的网站，发现印有数字的气球以不同的组合包形式出售，每个包包含不同大小、颜色和数字的气球。Kate 并不关心气球的大小、颜色或其他属性，她只关心气球上的数字。幸运的是，商店提供了所有可用的气球包信息。Kate 通过商店的 REST API 获取了这些信息，并提取了她所需的部分——每个包的价格以及气球上的数字。

请帮助 Kate 完成最后的任务：找出她可以购买的最便宜的气球包，以获得她庆祝 2021 所需的四个数字。

## 说明/提示

在第一个样例中，第 2 个和第 3 个气球包包含数字 $\texttt{2}$、$\texttt{0}$、$\texttt{2}$、$\texttt{1}$，而第 3 个包是最便宜的。

翻译由 DeepSeek V3 完成

## 样例 #1

### 输入

```
4
100 9876543210
200 00112233445566778899
160 012345678924568
150 000000123456789```

### 输出

```
3```

## 样例 #2

### 输入

```
5
100 0123456789
120 0022446688
200 00224466883456789
10 0
10 1```

### 输出

```
0```

# 题解

## 作者：封禁用户 (赞：3)

## 题目大意
[题目传送门](https://www.luogu.com.cn/problem/P12860)
## 题目分析
希望审核大大给过。

这是一道模拟题，由于数据过大，所以使用 string。这里可以使用 `find` 函数来查找，如果 $2$ 有两个，$1$ 和 $0$ 个有一个，那么就将 $p$ 和目前最小值比较，如果比最小值要小，就再用一个变量记录下标，并更新最小值即可。

下面是代码。
## 题目[代码](http://luogu.com.cn/record/220815283)
```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
#define uint unsigned long long
#define speed ios::sync_with_stdio(0),cin.tie(0), cout.tie(0);
int n;
signed main() {
	speed
	int minn=INT_MAX,mini=0;
	cin>>n;
	for(int p=1;p<=n;p++){
		int a;
		string b;
		cin>>a>>b;
		if(b.find('2')!=-1&&b.find('0')!=-1&&b.find('1')!=-1){
			int k=0;
			for(int i=0;i<b.size();i++)if(b[i]=='2')k++;
			if(k>=2)
				if(a<minn)minn=a,mini=p;
		}
	}
	cout<<mini;
	return 0;
}

//关注一下作者吧，一定会馆！！！
```

---

## 作者：easy42 (赞：3)

这道题要求我们找出最小满足要求的字符串，我们需要判断每个数字出现多少次，可以使用数位分离法，开变量记录即可。

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,h=1,t,ans=INT_MAX,k;
string s;
int main(){
    cin>>n;
    while(h<=n){
        cin>>t>>s;
        int a=0,b=0,c=0;
        for(int i=0;i<s.size();i++){
            if(s[i]=='2') a++;
            if(s[i]=='0') b++;
            if(s[i]=='1') c++;
        }
        if(a>=2&&b>=1&&c>=1){
            if(t<=ans) k=h,ans=t;
        }
        h++;
    }
    cout<<k;
    return 0;
}
```

---

## 作者：Clare613 (赞：3)

## 思路：
本题运用了结构体排序，我们可以根据价格来排一下序，然后按照排序结果找到第一个符合要求的，输出它的 $id$ 即可。\
判断方法：对于字符串，找到是否有至少一个 `0`，一个 `1`，两个 `2`，对于符合以上条件的就是符合的。
## code：
```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
struct node{
	int p,id;
	string x;
	void read(){
		cin>>p>>x;
	}
}a[1005];
bool cmp(node x,node y){
	return x.p<y.p;
}
bool f(string x){
	int cnt[10]={};
	for(int i=0;i<x.size();i++){
		cnt[x[i]-'0']++;
	}
	return cnt[0]>=1&&cnt[1]>=1&&cnt[2]>=2;
}
signed main(){
	cin.tie(0)->sync_with_stdio(0);
	int n;
	cin>>n;
	for(int i=1;i<=n;i++){
		a[i].read();
		a[i].id=i;
	}
	sort(a+1,a+n+1,cmp);
	for(int i=1;i<=n;i++){
		if(f(a[i].x)){
			cout<<a[i].id;
			return 0;
		}
	}
	cout<<0;
	return 0;
}
```

---

## 作者：ttyy0518 (赞：2)

## 题目简述

输入一个整数 $n$, 再输入 $n$ 行，每行输入一个整数 $p$ 和一个字符串 $a$。求字符串 $a_i$ 包含 $2021$ 时，$p$ 的最小值。

## 解题思路

一道简单的入门题。

- 我们可以把每个字符串 $a_i$ 的每一位取出来存到一个数组中。
- 再判断数组是否包含一个 $1$，两个 $2$ 和一个 $0$。
- 包含时比较 $p_i$ 的大小是否小于之前满足条件的 $p$ 的大小，小于就把索引存起来，最后输出索引。

Tip：要注意如果没有数组包含 $2021$，最后要输出 $0$。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,p[1005],minn=INT_MAX,s;
string a[1005];
bool l=0;
int main(){
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>p[i]>>a[i];
		int lg[11]={};
		for(int j=0;j<a[i].size();j++)lg[a[i][j]-'0']++;
		if(lg[0]>=1 && lg[2]>=2 && lg[1]>=1){
			l=1;
			if(p[i]<minn){
				minn=p[i];
				s=i;
			}
		}
	}
	if(l)cout<<s;
	else cout<<0;
	return 0;
}
```

### [记录](https://www.luogu.com.cn/record/220858973)

---

## 作者：yzbzz147268 (赞：2)

### [P12860 [NERC 2020 Online] Kate' s 2021 Celebration](https://www.luogu.com.cn/problem/P12860) 题解
---
#### 题意：

给出 $n$ 个字符串 $s$ 和价值 $w$ 求出字符串里包含 $2021$ 这几个数的最小价值的字符串编号。


---

#### 分析：
题目要求我们求出最小的价值，于是我们可以定义一个结构体，然后按照输入的价值来排序。

```cpp
struct node{//定义结构体
    int w,u;//价值，编号
    char s[105];//气球包
}a[1005];
int cmp(node a,node b){//按价值排序
    return a.w<b.w;
}
```
然后我们再判断

气球包是否满足条件，满足直接输出即可。


---

#### 代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
struct node{//定义结构体
    int w,u;//价值，编号
    char s[105];//气球包
}a[1005];
int cmp(node a,node b){//按价值排序
    return a.w<b.w;
}
int main(){
    int n;
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>a[i].w>>a[i].s;
        a[i].u=i;//当前编号
    }
    sort(a+1,a+1+n,cmp);//排序
    for(int i=1;i<=n;i++){
        int l=strlen(a[i].s);//获取长度
        int a0=0,a1=0,a2=0;
        for(int j=0;j<l;j++){
            if(a[i].s[j]=='2') a2++;
            if(a[i].s[j]=='1') a1++;
            if(a[i].s[j]=='0') a0++;
        }
        if(a2>=2&&a0>=1&&a1>=1){//是否满足
            cout<<a[i].u<<endl;
            return 0;//直接结束
        }
    }
    cout<<0<<endl;
    return 0;
}
```

---

## 作者：Gilbert1206 (赞：2)

## 题解：P12860 [NERC 2020 Online] Kate' s 2021 Celebration

[题目传送门](https://www.luogu.com.cn/problem/P12860)

## 思路
一道简单的模拟题，统计一个字符串有几个 $0$，$1$，$2$。如果满足条件则看谁的价格更低，最后输出其下标就可以了。

## code

```cpp
#include<bits/stdc++.h>
using namespace std;
int a[10];
int main(){
	int n;
	cin>>n;
	int id=0,ans=1e9;
	for(int i=1;i<=n;i++){
		int coin;
		cin>>coin;
		string p;
		cin>>p;
		memset(a,0,sizeof(a));
		for(int j=0;j<p.size();j++){
			a[p[j]-'0']++;
		}
		if(a[0]>=1&&a[1]>=1&&a[2]>=2){
			if(coin<ans){
				ans=coin;
				id=i;
			}
		}
	} 
	cout<<id;
	return 0;
}
```

---

## 作者：Vct14 (赞：2)

对于每个气球包，开一个桶记录每个数字出现了多少次。如果 $2$ 出现的次数大于等于 $2$ 且 $1,0$ 出现的次数大于等于 $1$ 那么可以购买该气球。用两个变量分别记录当前可以购买的最便宜的气球包的价格和编号即可。

```cpp
#include<bits/stdc++.h>
using namespace std;

int main(){
    int n;cin>>n;int mn=1e6,mz=0;
    for(int i=1; i<=n; i++){
        int p;string s;cin>>p>>s;
        int num[10]={0};
        for(int i=0; i<s.size(); i++) num[s[i]-'0']++;
        if(num[2]>=2 && num[1]>=1 && num[0]>=1 && p<mn) mn=p,mz=i;
    }
    cout<<mz;
	return 0;
}
```

---

## 作者：Hanrui1206 (赞：1)

## 【题目大意】
判断字符串中是否存在**至少** $2$ 个 $2$，$1$ 个 $0$，$1$ 个 $1$。如果有多个输出 $p$ 最小的一项的**编号**。  

## 【解题思路】
逐个判断。
 
定义 $3$ 个变量 $a$、$b$、$c$，记录 $2$、$0$、$1$，出现的次数，在进行判断是否满足条件。

额外定义两个变量 $minn$、$p$，分别记录最便宜的价格和最便宜的套装的**编号**。

## 【关键程序】
```cpp
for (int i = 1; i <= str.size(); i ++) {
  if (str[i] == '2') {
    a ++;
  } else if (str[i] == '0') {
    b ++;
  } else if (str[i] == '1') {
    c ++;
  }
}
```

---

## 作者：_Epsilon_ (赞：0)

# 题意
Kate 在买气球，每个气球有自己的数字。Kate 喜欢包含 `2` `0` `2` `1` 四个数字的气球（无论顺序）。现在她要找到最便宜的气球。
# 思路
模拟即可，使用字符串存储气球数字，然后用一个数组存储每个数字计算的次数，要是 `2` 出现的次数 $cnt_2 \ge 2$，`0` 出现的次数 $cnt_0 \ge 1$，`1` 出现的次数 $cnt_1 \ge 1$，这个气球就是 Kate 要的。最后比较找出最小值即可。

记得给统计数组 `cnt` 重置。
# 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
long long n,a,price,ans=0,cnt[15]={};
string s;
int main()
{
    cin>>n;
    price=10000000;
    for(int i=1;i<=n;++i)
        {
            cin>>a>>s;
            for(int j=0;j<s.size();++j)
                {
                    cnt[int(s[j])-int('0')]++;
                }
            if(cnt[2]>=2&&cnt[0]>=1&&cnt[1]>=1)
            {
                if(a<price)
                {
                	ans=i;
                	price=a;
				}
            }
            cnt[2]=0;
            cnt[0]=0;
            cnt[1]=0;
        }
    cout<<ans<<endl;
    return 0;
}
```

---

## 作者：furina_yyds (赞：0)

# P12860 [NERC 2020 Online] Kate' s 2021 Celebration 题解

## 题意

给定 $n$ 个气球的价格和数字，请你求出最便宜的包含 $2$ 个 $2$，$1$ 个 $0$，$1$ 个 $1$。

## 思路

使用字符串模拟即可。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int main(){
    int n, ans = 0, minn = 2e9;
    scanf("%d", &n);
    for(int i = 1, p; i <= n; i++){
        string s;
        scanf("%d", &p);
        cin >> s;
        int _2 = 0, _0 = 0, _1 = 0;
        for(int j = 0; j < s.size(); j++){
            if(s[j] == '2')_2++;
            if(s[j] == '0')_0++;
            if(s[j] == '1')_1++;
            if(_2 >= 2 && _1 >= 1 && _0 >= 1 && p < minn){
                ans = i, minn = p;
            }
        }
    }
    printf("%d", ans);
    return 0;
}
```

---

## 作者：DemonPlayer (赞：0)

### 思路：
对于每个气球包，记录 $0,1,2$ 的数量，如果 $0,1$ 的数量大于 $1$，$2$ 的数量大于 $2$。说明这个气球包可以使用，记录最小花费的编号，输出。
```cpp
#include<bits/stdc++.h>
using namespace std;

int n,pr,minn=1e9,idx,tot0,tot2,tot1;
string s;

int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		cin>>pr>>s;
		tot0=tot1=tot2=0;
		for(int j=0;j<s.size();j++){
			tot0+=(s[j]=='0');
			tot1+=(s[j]=='1');
			tot2+=(s[j]=='2');
		}
//		cout<<tot1<<' '<<tot0<<' '<<tot2<<'\n';
		if(tot2>=2&&tot0>=1&&tot1>=1){
			if(pr<minn){
				minn=pr;
				idx=i;
			}
		}
	}
	cout<<idx;
	return 0;
}
```

---

## 作者：_luogu_huowenshuo_ (赞：0)

## 思路
要购买含至少两个 $2$、一个 $0$、一个 $1$ 的最便宜气球包。

检查是否满足条件（$c_2 \geq 2, c_0 \geq 1, c_1 \geq 1$）。

最后输出满足条件的最低价格和对应包编号，输出编号或 $0$。
## 代码
```cpp
#include<iostream>
#include<string>
#include<climits>
using namespace std;
int n,p[1145];
string s[1145];
int main()
{
    cin>>n;
    for(int i=1;i<=n;i++)
    cin>>p[i]>>s[i];
    int mn=INT_MAX,ans=0;
    for(int i=1;i<=n;i++){
        int c[10]={0};
        for(int j=0;j<s[i].size();j++)
            c[s[i][j]-'0']++;
    if(c[2]>=2&&c[0]>=1&&c[1]>=1)
        if(p[i]<mn){
            mn=p[i];
            ans=i;
        }
    }
    cout<<ans;
    return 0;
}
```

---

