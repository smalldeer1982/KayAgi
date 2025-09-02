# [USACO23JAN] Leaders B

## 题目描述

Farmer John has $N$ cows $(2 \le N \le 10^5)$. Each cow has a breed that is either Guernsey or Holstein. As is often the case, the cows are standing in a line, numbered $1 \cdots N$ in this order.

Over the course of the day, each cow writes down a list of cows. Specifically, cow $i$
's list contains the range of cows starting with herself (cow $i$) up to and including cow $E_i(i \le E_i \le N)$.

FJ has recently discovered that each breed of cow has exactly one distinct leader. FJ does not know who the leaders are, but he knows that each leader must have a list that includes all the cows of their breed, or the other breed's leader (or both).

Help FJ count the number of pairs of cows that could be leaders. It is guaranteed that there is at least one possible pair. 

## 说明/提示

### Explanation for Sample 1

The only valid leader pair is $(1,2)$. Cow $1$'s list contains the other breed's leader (cow $2$). Cow $2$'s list contains all cows of her breed (Holstein).

No other pairs are valid. For example, $(2,4)$
is invalid since cow $4$'s list does not contain the other breed's leader, and it also does not contain all cows of her breed.

### Explanation for Sample 2

There are two valid leader pairs, $(1,3)$ and $(2,3)$.

### Scoring

 - Inputs $3-5$: $N \le 100$  
 - Inputs $6-10$: $N \le 3000$
 - Inputs $11-17$: No additional constraints.

## 样例 #1

### 输入

```
4
GHHG
2 4 3 4```

### 输出

```
1```

## 样例 #2

### 输入

```
3
GGH
2 3 3```

### 输出

```
2```

# 题解

## 作者：LegendaryGrandmaster (赞：14)

[铜组全部题解](https://www.luogu.com.cn/blog/686297/usaco-2023-cu-ti-xie)

2023.2.18 修复代码 bug。

hack 数据：
```
4
GHHG
4 3 3 4
```

贪心。能想到的话其实代码很短。

我们可以把选择的两个领导分为两种情况：

1. 有一个领导可以管理自己所有种类的牛，且另外一个领导可以管理这个领导。

2. 两个领导都可以管理各自种类的牛。 

把这个想出来代码也就自然好写了。

我们可以先把两种种类**第一次**和**最后一次**出现的牛出现的位置找出来。

之后我们可以看到，如果这头牛能管控的牛可以当领导（那么这个被管控的领导管控的牛必须包括所有和自己种类一样的牛），如果满足，那么就形成一对。

如果两头牛都可以管控所有和自己种类一样的牛，那么也是一对。

**注**：另外需要注意，如果之前两头牛已经成为一组，则不算。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std; 
const int N=1e5+10;
int a[N];
signed main() 
{ 
    int n;
    cin>>n;
    string st;
    cin>>st;
    st=' '+st;
    int g=0,h=0,G=0,H=0;
    for(int i=1;i<st.size();i++){
        if(st[i]=='G'&&!g)g=i;
        else if(st[i]=='H'&&!h)h=i;
    }
    for(int i=st.size()-1;i>=1;i--){
        if(st[i]=='G'&&!G)G=i;
        else if(st[i]=='H'&&!H)H=i;
    }
    for(int i=1;i<=n;i++)cin>>a[i];
    char ch;
    int ans=0;
    bool gg=0,hh=0;
    for(int i=1;i<=n;i++){
        if(st[i]=='G'){
            if(a[i]>=h&&i<=h&&a[h]>=H){
            	ans++;
            	if(i==g)gg=1;
            }
        }
        if(st[i]=='H'){
            if(a[i]>=g&&i<=g&&a[g]>=G){
            	ans++;
            	if(i==h)hh=1;
            }
        }
    }
    /*
    为了防止抄题解，代码里可能会有废话/ww
    管控另外一个领导的定义如下：这个牛所管理的范围可以包含另外一种牛第一次出现的位置。
    管理包括所有和自己种类一样的牛的定义如下：这个牛所管理的范围可以包含和自己种类一样的牛最后一次出现的位置。
    */
    if(a[g]>=G&&a[h]>=H&&!gg&&!hh)ans++;
    cout<<ans;
}

```

---

## 作者：鱼跃于渊 (赞：13)

2023.2.18 修复代码 bug。  
hack 数据：
```
4
GHHG
4 3 3 4
```

# solution:
首先根据题目要求，一只奶牛能被选为首领的条件只有 `包含另一种类的首领` 或 `包含同种类的所有奶牛` 。显而易见，两个首领中最多只有一个能满足第一个条件，并且满足第二个要求的必定为从左至右的第一只某种类的奶牛。另外还要注意，两只满足第一个条件的奶牛也能凑成一对。所以做法如下： 
1. 找出从左至右第一只当前种类的奶牛，并判断他是否满足条件二；   
2. 枚举所有奶牛，并判断它是否包含另一种类满足条件二的奶牛，有则答案加一；
3. 判断步骤一中找出的两只奶牛是否有包含，无则答案加一。              

温馨提示，数据中有同种类间都不满足条件二的情况出现，所以上述步骤都需另外判断是否有满足条件二的某种类奶牛。  
# code:
```
#include <bits/stdc++.h>
using namespace std;
char op;
int n,fg,fh,gmax,hmax,ans,a[100005],b[100005];
//a 为种类，b 为管辖范围
int main(){
	ios::sync_with_stdio(false);
	cin.tie(0);cout.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++){
		cin>>op;
		if(op=='G'){
			a[i]=1;gmax=i;
		}else{
			a[i]=2;hmax=i;
		}
	}
	for(int i=1;i<=n;i++)
		cin>>b[i];
	//找满足第二条件的奶牛
	for(int i=1;i<=n;i++){
		if(a[i]==2) continue;
		if(b[i]>=gmax) fg=i;
		break;
	}
	for(int i=1;i<=n;i++){
		if(a[i]==1) continue;
		if(b[i]>=hmax) fh=i;
		break;
	}
	//枚举满足第一条件的奶牛
	for(int i=1;i<=n;i++){
		if(fg&&a[i]==2&&i<fg&&b[i]>=fg) ans++;
		if(fh&&a[i]==1&&i<fh&&b[i]>=fh) ans++;
	}
	//特判
	if(fg&&fh&&b[min(fg,fh)]<max(fg,fh)) ans++;
	cout<<ans<<'\n';
    return 0;
}
```

---

## 作者：陈嘉逸2012 (赞：3)

发现题解区里的解法咋都那么麻烦呢？这里介绍一种非常简单的方法，希望大家喜欢！
## 题意简述
这道题要求我们找出可能成为两种奶牛（根西岛 `G` 和荷斯坦 `H`）的“领导者”的所有可能的奶牛对。成为“领导者”的条件是：
1. 其记录的名单上包含它的品种的所有奶牛。
2. 其记录的名单上记录了另一品种奶牛的“领导者”。
## 思路
首先我们先找出第一种牛（假设为 `G` 品种）的最后一个牛的位置 $r$，再找出第二种牛（假设为 `H` 品种）的第一个牛的位置 $l$。

找出领导者对的判断条件为 $i=1 \land E_i \ge r \lor E_i \ge l$，解释如下：
* $i=1 \land E_i \ge r$：如果当前奶牛是第一头奶牛，并且它的名单结束位置 $E_i \ge r$（即包含所有 `G` 品种奶牛），则它可以是一个领导者。这是因为如果第一头奶牛是 `G`，它需要知道所有 `G` 品种奶牛的信息。
* $E_i \ge l$：对于其他奶牛（不是第一头奶牛），如果它们的名单结束位置 $E_i \ge l$（即包含第一个 `H` 品种奶牛的位置），则它们也可以是一个领导者。
这是因为这些奶牛需要知道至少一个 `H` 品种奶牛的信息。

两种条件满足一条即可。
## Code
```cpp
#include<bits/stdc++.h>
using namespace std;
const int maxn=2e5+5;
char s[maxn];
int n,l,r,e[maxn],ans;
int main(){
	cin>>n>>(s+1);
	for(int i=1;i<=n;i++) cin>>e[i];
	for(int i=1;i<=n;i++){
		if(s[i]==s[1]) r=i;
	}
	for(int i=2;i<=n;i++){
		if(s[i]!=s[1]){l=i;break;}
	}
	for(int i=1;i<l;i++){
		if((i==1&&e[i]>=r)||e[i]>=l) ans++;
	}
	cout<<ans;
}
```
**纯原创，想了好久，求赞！**

---

