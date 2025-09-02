# Character Swap (Easy Version)

## 题目描述

### 题意简述

给定两个长为 $n$ 的字符串 $s,t$。

您需要进行一次交换：找到一组 $i,j$ 满足 $1\leq i,j \leq n$，交换 $s_i$ 和 $t_j$。

问是否可以通过这次交换使得 $s=t$。

注意：您不能不进行交换。

## 样例 #1

### 输入

```
4
5
souse
houhe
3
cat
dog
2
aa
az
3
abc
bca
```

### 输出

```
Yes
No
No
No
```

# 题解

## 作者：Dream__Sky (赞：2)

本题暴力复杂度 $O(Tn^2)$，达到了恐怖的 $10^9$，所以我们考虑 $O(Tn)$ 做法。

首先我们发现，只有当两个字符串仅出现两处不同时才能有合法的方案。

然后当满足这个条件时，我们可以观察样例 1，如果同一个字符串在不同的两个位置上是一样的，那么就能交换。

如：

`SouSe`

`HouHe`
 
不同的位置上，第一个字符串是两个 `s`，第二个字符串是两个 `h`。

知道了这个之后，代码就好写了。

code：
```cpp
#include <bits/stdc++.h>
using namespace std;
string work()
{
	int n,cnt=0;
	string s1,s2;
	int a[10];
	
	cin>>n;
	cin>>s1>>s2;
	for(int i=0;i<n;i++)
	{
		if(s1[i]!=s2[i]) a[++cnt]=i;//记录不同的位置的下标
		if(cnt>2) return "No";//只能出现两组错误
	}
	if(cnt!=2) return "No";//同上
	
	if(s1[a[1]]==s1[a[2]]&&s2[a[1]]==s2[a[2]]) return "Yes";//判断是否相同
	return "No";
}
int main()
{
	int T;
	cin>>T;
	while(T--)
		cout<<work()<<endl;//T组数据
	return 0;
}
```


---

## 作者：qinmingze (赞：1)

### [题目传送门](https://www.luogu.com.cn/problem/CF1243B1)
## 题意
现在有两个字符串，问能不能在进行完一次交换操作后，让两个字符串一样。
## 思路
- 只进行**一次**交换操作，，意味着当**有两个字符串中只有两个不同的字符时才能进行交换操作**，同时**操作方案只有一种**:


------------

![](https://cdn.luogu.com.cn/upload/image_hosting/c0q0z6uc.png?x-oss-process=image/resize,m_lfit,h_340,w_450)

------------

# AC 代码
```cpp
#include<bits/stdc++.h>

using namespace std;

int main(){
	int T;
	cin >> T;//T组数据
	while(T--){
		int n;
		cin >> n;
		string s, t;
		cin >> s >> t;
		string f[2];//存字符串s和字符串t之间不同的字符
		for(int i = 0; i < n; i++){
			if(s[i] != t[i]){
				f[0] += s[i];
				f[1] += t[i];
			}
		}
      //判断条件：1.长度相同都为2  2.可以一次交换成功的条件
		if(f[0].size() == 2 && f[1].size() == 2 && f[1][0] == f[1][1] && f[0][0] == f[0][1])cout << "Yes" << endl;
		else cout << "No" << endl;
	}
    return 0;
}
```

------------

### [已AC](https://www.luogu.com.cn/record/98918680)

---

## 作者：御前带刀侍卫 (赞：1)

### 0.题目链接

[CF1243 B1 in luogu](https://www.luogu.org/problem/CF1243B1)

### 1.读题

挺有意思一题目，

每组数据给你两个不同的字符串，

问你只交换两个字符串中的一个字符能不能使这个字符串变得相同。

### 2.思考

首先先观察样例（~~emmm……好像没什么好康的~~）

实际上他的性质很普通（~~废话~~），

但由**样例1**我们可以想出一个简化思路的贪心：

**两数组中相同的位置不需要考虑或交换**

而我们只能交换一次

所以：如果有一个或3个及以上不同则无法交换

如果两个不同的位置在同一字符串中不对应同样的字符也不能交换

唯一的交换方案就是：

![](https://s2.ax1x.com/2019/11/07/MFuk0U.png)

这样的

### 3.代码

所以我们就考虑存一下不同的位置

（有离散化的思想，只需保证其相对顺序不变即可）

```cpp
#include<iostream>
#include<stdio.h>

using namespace std;

void solve(){
	int n;
	string a,aa="",b,bb="";     //aa/bb分别为不同的位置在两字符串中的对应 
	cin>>n;
	cin>>a>>b;
	for(int i=0;i<n;i++){
		if(a[i]!=b[i]){
			aa+=a[i];
			bb+=b[i];
		}
	}
	if(aa.length()!=2||bb.length()!=2){
		printf("No\n");
		return;
	}
	if(aa[0]!=aa[1]||bb[0]!=bb[1]){
		printf("No\n");
		return;	
	}
	if(aa[0]==aa[1]&&bb[0]==bb[1]){  //就是上面的方法啦 
		printf("Yes\n");
		return;
	}
}

int main(){
	int q;
	cin>>q;                           
	for(int i=0;i<q;i++){             //多组数据 
		solve(); 
	}
}
```
嗯，就酱



---

## 作者：rain_dew (赞：0)

原题目传送门：[CF1243B1](solution)

一道模拟题，想通后就很简单。

### 题意：
根据两个字符串 $s$ 与 $t$ 必须**进行一次交换**，使得两串相同。

### 思路：
读入后查找不同之处，由题目可知，交换必须要保证**两对**代换项。

设 $cnt$ 记录两串的不同之处并记录，若记录后出现 $cnt \ne 2$ 情况，立刻输出 `No` 结束。

否则如下比较，如果交叉交换后字符串相同，输出 `Yes`，否则输出 `No`。

![](https://cdn.luogu.com.cn/upload/image_hosting/qp69dlo2.png)

### 注意：
+ 本题目多测，注意换行与清空。

### 代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
int T,n,f[3],len,cnt;
string s,t;
int main()
{
	cin>>T;
	while (T--)
	{
		cin>>n;
		cin>>s>>t;
		len=s.length(),cnt=0;
		for (int i=0;i<len;i++)
			if (s[i]!=t[i])
			{
				++cnt;
				if (cnt>2)
					break;
				f[cnt]=i;
			}
		if (cnt>2 || cnt<2)
		{
			cout<<"No"<<endl;
			continue;
		}
		swap(s[f[1]],t[f[2]]);
		if (s==t)
			cout<<"Yes"<<endl;
		else
			cout<<"No"<<endl;
	}
	return 0;
}
```

---

## 作者：HEzzz (赞：0)

[题目跳转键](https://www.luogu.com.cn/problem/CF1243B1)

## 题目大意

给你两个字符串 $s$ 和 $t$，让你找出两个数 $i$ 和 $j$，把 $s_i$ 和 $t_j$ 交换，使得 $s=t$。

---

这道题有一个关键点，就是只能交换一次，进而我们可以知道要想 $s=t$，那么 $s$ 和 $t$ 仅有两个字符不相同，则满足条件的情况只有一种，如下图。

![](https://cdn.luogu.com.cn/upload/image_hosting/hik72nzl.png)

(图片有点丑，大家将就将就捏 QwQ

code

```cpp
#include<bits/stdc++.h>
#define _rep(i,a,b) for(int i=(a);i<=(b);i++)
#define _antirep(i,a,b) for(int i=(a);i>=(b);i--)
using namespace std;
typedef long long lxl;
int G,n;
char s[10010],t[10010];
int main() 
{
	cin>>G;
	while(G--)
	{
		cin>>n;
		cin>>(s+1)>>(t+1);
		int cnt=0;
		string h[2]={"",""};
		_rep(i,1,n)
		{
			if(s[i]!=t[i])
			{
				cnt++;
				h[0]+=s[i];
				h[1]+=t[i];
			}	
		} 
		if(cnt>2) cout<<"No";
		else if(cnt==2&&h[0][0]==h[0][1]&&h[1][0]==h[1][1]) cout<<"Yes";
		else cout<<"No";
		cout<<"\n"; 
	} 
	return 0;
}
```


---

## 作者：sssscy_free_stdio (赞：0)

这是蒟蒻写的第三篇题解~

这题题意很简单，就是找一组 $i,j$，交换 $s_i$ 和 $t_j$，使得 $s=t$。

由于只能交换一次，因此只有 $s$ 和 $t$ 只有两个不同时才成立。

接着这个情况观察样例，可以发现只有 $s$ 和 $t$ 都各自在不同的两个位置上是相同的，条件才成立。

因此就可以 `for` 一遍，把不同的两个位置上的字符分别放到一个数组里，再判断一遍就好啦~

AC CODE:
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k;
string s,t,cnt[10];
int main(){
	scanf("%d",&k);
	while(k --> 0){
		scanf("%d",&n);
		cin>>s>>t;
		cnt[1].clear(),cnt[2].clear();//清空
		int lencnt=0;
		for(int i=0;i<n;i++){
			if(s[i]!=t[i]){//不相同
				lencnt++;
				cnt[1]+=s[i],cnt[2]+=t[i];//各自放入数组
			}
		}if(lencnt==2&&cnt[1][0]==cnt[1][1]&&cnt[2][0]==cnt[2][1]){//判断是否只有两个不同且在不同的两个位置上是相同的
			printf("yes\n");
		}else{
			printf("no\n");
		}
	}
	return 0;
}
```

---

## 作者：Digital_Sunrise (赞：0)

## CF1243B1题解

[CF题解合集(包括本场)](https://www.luogu.com.cn/blog/yl2330/I-Love-YR-Forever)

[Markdonw源代码](https://yhwh-group.coding.net/public/codingwiki/files/git/files/master/blog/CF1243/B1.Markdown)

### 思路

既然正着不好想，我们就倒着想 。

假如我们现在有两个相同字符串 $a$ 和 $b$ 。

我们准备交换 $a_i$ 和 $b_j$ 使得这两个字符串符合题目条件 。

交换后由

| 字符串 | 第 $i$ 位 | 第 $j$ 位 |
| :----------: | :----------: | :----------: |
| $a$ | $a_i$ | $a_j$ |
| $b$ | $b_i$ | $b_j$ |

变为

| 字符串 | 第 $i$ 位 | 第 $j$ 位 |
| :----------: | :----------: | :----------: |
| $a$ | $b_j$ | $a_j$ |
| $b$ | $b_i$ | $a_i$ |

因为原字符串 $a = b$，

所以 $a_i=b_i,a_j=b_j$。

所以变换后字符串（记为 $A,B$）的第 $i,j$ 位都分别相同，

即 $A_i=A_j$ 且 $B_i=B_j$。

所以只要判断读入的字符串 $s,t$ 是否**有且仅有两位不等且这两位字符在每个字符串分别相等**即可。

注意，所有字符均相等的字符串也是可行的，因为可以讲两个相等字符串互换。

### Code

```cpp
#include <bits/stdc++.h>
using namespace std;

string s,t;
int n,T;
int c1,c2;

void solve()
{
    c1 = c2 = -1;
    int sum = 0;
    for(int i = 0;i < n;i++)
    {
        if(s[i] != t[i])
        {
            sum++;
            if(c1 == -1)
                c1 = i;
            else
                c2 = i;
        }
        if(sum > 2)
        {
            printf("No\n");
            return;
        }
    }
    if(sum != 2)
    {
        printf("No\n");
        return;
    }
    if(s[c1] == s[c2] and t[c2] == t[c1])
    {
        printf("Yes\n");
        return;
    }
    printf("No\n");
}

int main()
{
    cin >> T;
    while(T--)
    {
        cin >> n;
        cin >> s;
        cin >> t;
        solve();
    }
    return 0;
}
```

---

