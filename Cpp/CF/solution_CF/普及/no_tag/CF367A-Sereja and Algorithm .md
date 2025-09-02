# Sereja and Algorithm 

## 题目描述

Sereja loves all sorts of algorithms. He has recently come up with a new algorithm, which receives a string as an input. Let's represent the input string of the algorithm as $ q=q_{1}q_{2}...\ q_{k} $ . The algorithm consists of two steps:

1. Find any continuous subsequence (substring) of three characters of string $ q $ , which doesn't equal to either string "zyx", "xzy", "yxz". If $ q $ doesn't contain any such subsequence, terminate the algorithm, otherwise go to step 2.
2. Rearrange the letters of the found subsequence randomly and go to step 1.

Sereja thinks that the algorithm works correctly on string $ q $ if there is a non-zero probability that the algorithm will be terminated. But if the algorithm anyway will work for infinitely long on a string, then we consider the algorithm to work incorrectly on this string.

Sereja wants to test his algorithm. For that, he has string $ s=s_{1}s_{2}...\ s_{n} $ , consisting of $ n $ characters. The boy conducts a series of $ m $ tests. As the $ i $ -th test, he sends substring $ s_{li}s_{li}+1...\ s_{ri} $ $ (1<=l_{i}<=r_{i}<=n) $ to the algorithm input. Unfortunately, the implementation of his algorithm works too long, so Sereja asked you to help. For each test $ (l_{i},r_{i}) $ determine if the algorithm works correctly on this test or not.

## 说明/提示

In the first example, in test one and two the algorithm will always be terminated in one step. In the fourth test you can get string "xzyx" on which the algorithm will terminate. In all other tests the algorithm doesn't work correctly.

## 样例 #1

### 输入

```
zyxxxxxxyyz
5
5 5
1 3
1 11
1 4
3 6
```

### 输出

```
YES
YES
NO
YES
NO
```

# 题解

## 作者：qjxqjx (赞：1)

## 题目大意：
给出一个字符串，元素只有 x,y,z 这三种，现在给出一个区间$[l,r]$，这个区间内的字符可以任意调换，如果变换之后这个区间字符串的所有子串都是 ```zyx``` 或 ```xzy``` 或 ```yxz``` 的话，输出  ```yes```（若 $r-l<2$ 也输出 ```YES```），否则输出```NO```。

## 题目思路：
这题我们分情况讨论：

第一点，根据题意，当 $r-l<2$ 我们就直接输出 YES 即可。

第二点，与题意相反，当 $r-l>=2$ 时，也就是只能当这个区间中的 x 的个数，y 的个数，z 的个数两两之差都小于 2 的时候，才可以输出 YES。

综上所述，我们梳理一下：  
我们先遍历字符串，统计下在 $str_i$ 之前的 x 的个数、y 的个数和 z 的个数。之后我们用到哪个区间就可以把哪个区间的 x、y、z 的个数取出来作判断即可完成此题。

## 代码：
```c
#include<bits/stdc++.h>
//#include<cstdio>
#define maxn 123456
using namespace std;
int dpx[maxn],dpy[maxn],dpz[maxn];
char str[maxn];//注意类型
int m,l,r;
int main(){
    while(~scanf("%s",str)){
        int len=strlen(str);
        memset(dpx,0,sizeof(dpx));
        memset(dpy,0,sizeof(dpy));
        memset(dpz,0,sizeof(dpz));
        //memset必写，因为是多组数据，每次要清空
        int x=0,y=0,z=0;
        for(int i=0; i<len; i++){
            if(str[i]=='x'){
  				x++;
            }else if(str[i]=='y'){
  				y++;
            }else{
  				z++;
  			}
            dpx[i+1]=x;
            dpy[i+1]=y;
            dpz[i+1]=z;
        }
        cin>>m;
        while(m--){
            cin>>l>>r;
            if(r-l<2){//第一种情况
             	cout<<"YES"<<endl;
            }else{//第二种情况
                x=dpx[r]-dpx[l-1];
                y=dpy[r]-dpy[l-1];
                z=dpz[r]-dpz[l-1];
                if(abs(x-y)<2&&abs(z-y)<2&&abs(x-z)<2){//一定要取绝对值
                    cout<<"YES"<<endl;
                }else{
                    cout<<"NO"<<endl;
                }
            }
        }
    }
    return 0;
}
//用c语言会更快
```
另外送个c语言的代码：[code](https://www.luogu.com.cn/paste/8vocfnnd)

---

## 作者：ggc123 (赞：0)

## 思路

要解决这个问题，我们需要对给定的字符串区间 $[l, r]$ 进行分析，令 $len$ 为字串长度，即 $len=r-l+1$。

确保通过任意调换区间内的字符，可以使得所有子串都满足以下三种模式之一：

1. `"zyx"`
2. `"xzy"`
3. `"yxz"`

根据题目要求，我们可以将这个问题分解为几个步骤：

### 步骤 1: 区间长度检查

即当 $len < 3$ 时，直接输出 `YES`。

### 步骤 2: 统计字符出现次数

对于 $len \ge 3$ 的情况，我们需要确保区间内的字符可以被排列成以上有效的子串情况。为此，我们需要对区间内的字符进行计数。具体来说就是统计字符频率：统计区间 $[l, r]$ 内的字符 $x,y,z$ 的数量。

因为要多次用到区间 $[l, r]$ 内 $x,y,z$ 的数量，为了确保不会喜提 TLE，因此考虑使用前缀计数。

### 步骤 3: 验证频率是否匹配

如果变换之后这个区间字符串的所有子串都是以上 $3$ 种情况，那么这个区间内 $x,y,z$ 的数量差不超过 $1$。

## 代码

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int t, l, r, cntx[100005], cnty[100005], cntz[100005];
string s;
signed main() {
	cin.tie(0), cout.tie(0);
	cin >> s >> t;
	s = '$'+s ;
	for (int i = 1; i < s.size(); i++) {// 前缀计数
		cntx[i] = cntx[i - 1] + (s[i] == 'x' ? 1 : 0);
		cnty[i] = cnty[i - 1] + (s[i] == 'y' ? 1 : 0);
		cntz[i] = cntz[i - 1] + (s[i] == 'z' ? 1 : 0);
	}
	while (t--) {
		cin >> l >> r;
		if (r - l < 2) { //输出 YES
			cout << "YES\n";
			continue;
		}
		int x = cntx[r] - cntx[l - 1], y = cnty[r] - cnty[l - 1], z = cntz[r] - cntz[l - 1];// x,y,z 的数量
		if (abs(x - y) <= 1 && abs(y - z) <= 1 && abs(x - z) <= 1)	cout << "YES\n";
		else 	cout << "NO\n";
	}

	return 0;
}
```

---

## 作者：AC_love (赞：0)

不难发现，一个符合条件的区间在调换顺序后一定是形如 $\cdots\texttt{xzyxzyxzy}\cdots$ 的形式的，不难发现此时每个字符出现的次数的差不能超过 $1$。

那么我们就统计一下每个区间内 $\texttt{x,y,z}$ 的个数即可。

不过如果直接暴力统计的话显然会 T 飞的。对此有两种有效的优化：

1. 使用数据结构，如线段树
2. 前缀和优化

显然后者更好写且复杂度更低。

[点我查看代码](https://codeforces.com/contest/368/submission/234165912)

---

## 作者：LBYYSM_123 (赞：0)

### 题目大意
给出一个字符串，元素只有 $x$,$y$,$z$ 这三种，现给出一个区间 $[l,r]$，这个区间内的字符可以任意调换，如果变换之后这个区间字符串的所有子串都是 $zyx$ 或 $xzy$ 或 $yxz$ 的话，输出 `yes`（若 $r-l<2$ 也输出 `YES`），否则输出 `NO`。

------------
### 题目思路
通过**前缀和**预处理 $str_i$ 前的 $x$,$y$,$z$ 的数量。    

- 若 $r-l<2$，直接特判 `YES`。
- 若 $r-l\ge2$，当这个区间中的 $x$,$y$,$z$ 的个数两两之差都小于 $2$ 的时候，才可以输出 `YES`。

------------
### Code
```cpp
#include<bits/stdc++.h>
#define int long long
#define maxn 123456
using namespace std;
int dpx[maxn],dpy[maxn],dpz[maxn];
string str;
int m,l,r;
#define abs(x) ({						\
	long ret;					\
	if(sizeof(x)==sizeof(long)){		\
		long __x=(x);				\
		ret=(__x<0)?-__x:__x;		\
	} \
	else{					\
		int __x=(x);				\
		ret=(__x<0)?-__x:__x;		\
	}						\
	ret;						\
})
template<typename T>
inline bool abss(initializer_list<T> v){
	for(auto i:v){
		if(abs(i)>=2) 
			return 1;
	}
	return 0;
}
inline void fill_lian(initializer_list<int*> v){
	for(initializer_list<int*>::iterator it=v.begin();it!=v.end();it++)
		memset(*it,0,sizeof(*it));
}
signed main(){
	ios::sync_with_stdio(0);
	cin.tie(0),cout.tie(0);
    while(cin>>str){
    	fill_lian({dpx,dpy,dpz});
        int x=0,y=0,z=0;
        for(int i=0;str[i]!='\0';i++){
            if(str[i]=='x')
  				x++;
            else if(str[i]=='y')
  				y++;
            else
  				z++;
            dpx[i+1]=x,dpy[i+1]=y,dpz[i+1]=z;
        }
        cin>>m;
        while(m--){
            cin>>l>>r;
            if(r-l<2)
             	cout<<"YES\n";
			else{
                x=dpx[r]-dpx[l-1];
                y=dpy[r]-dpy[l-1];
                z=dpz[r]-dpz[l-1];
                if(abss({x-y,z-y,x-z})==1)
                    cout<<"NO\n";
                else
                	cout<<"YES\n";
            }
        }
    }
    return 0;
} 
```

---

## 作者：TLEWA (赞：0)

对于每次询问考虑一种构造法（且这是唯一的构造法）：

任选 $\texttt{zyx},\texttt{xzy},\texttt{yzx}$ 中的一个作为开头，然后根据末尾字母，在后面连接 $\texttt{zyx},\texttt{xzy},\texttt{yzx}$ 中的一个，可以发现 $x,y,z$ 的数量差距最大**不可超过**一（即最大为一），于是根据题意前缀和预处理，特判 $r-l<2$ 的情况，然后每次常数时间内回答询问即可。

代码如下：

```cpp
#include<bits/stdc++.h>

using namespace std;

string s;
int n,a[100005],b[100005],c[100005],l,r,maxn,minn;

int main() {
	while(cin >> s >> n) { //有多测，题目翻译没说清楚，坑人 
		memset(a,0,sizeof(a));
		memset(b,0,sizeof(b));
		memset(c,0,sizeof(c));
		for(int i=1;i<=s.length();++i) a[i]=a[i-1]+(s[i-1]=='x');
		for(int i=1;i<=s.length();++i) b[i]=b[i-1]+(s[i-1]=='y');
		for(int i=1;i<=s.length();++i) c[i]=c[i-1]+(s[i-1]=='z');
		for(int i=1;i<=n;++i) {
			cin >> l >> r; //l,r下标从1开始，题目翻译没说清楚，坑人 
			maxn=max(max(a[r]-a[l-1],b[r]-b[l-1]),c[r]-c[l-1]);
			minn=min(min(a[r]-a[l-1],b[r]-b[l-1]),c[r]-c[l-1]);
			if((maxn-minn)<2 || (r-l)<2) cout << "YES" << endl;
			else cout << "NO" << endl;
		}
	}
	return 0;
}
```


---

