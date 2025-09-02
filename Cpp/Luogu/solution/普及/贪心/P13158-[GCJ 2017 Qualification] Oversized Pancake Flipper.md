# [GCJ 2017 Qualification] Oversized Pancake Flipper

## 题目描述

去年，Infinite House of Pancakes 推出了一种新型煎饼。这种煎饼的一面（“开心面”）上有用巧克力豆做成的笑脸，另一面（“空白面”）则什么都没有。

你是当班的主厨。煎饼被排成一排在加热面上烹饪。为了进一步提升效率，餐厅最近给你配备了一个超大号煎饼翻转器，每次可以同时翻转恰好 $K$ 个连续的煎饼。也就是说，在这 $K$ 个煎饼的范围内，每个开心面朝上的煎饼会变为空白面朝上，反之亦然；煎饼的左右顺序不会改变。

你不能用翻转器翻转少于 $K$ 个煎饼，即使是在煎饼排的两端（因为加热面两侧有凸起的边界）。例如，你可以翻转最左边的 $K$ 个煎饼，但不能只翻转最左边的 $K-1$ 个煎饼。

你的学徒厨师还在学习工作，他刚刚用老式的单煎饼翻转器翻转了一些单独的煎饼，然后带着翻转器跑去洗手间了，正好在顾客即将参观厨房之前。现在你只剩下超大号煎饼翻转器，你需要尽快使用它，使所有正在烹饪的煎饼都开心面朝上，这样顾客才能满意地离开。

给定当前煎饼的状态，计算至少需要使用多少次超大号煎饼翻转器，才能让所有煎饼都开心面朝上；或者说明无法做到这一点。

## 说明/提示

**样例解释**

- 对于第 1 组测试用例，你可以先翻转最左边的 3 个煎饼，变为 ++++-++-，然后翻转最右边的 3 个，变为 ++++---+，最后再翻转剩下的 3 个空白面朝上的煎饼。还有其他方法可以用 3 次或更多次翻转完成，但没有比 3 次更少的方案。

- 对于第 2 组测试用例，所有煎饼已经全部开心面朝上，因此不需要翻转。

- 对于第 3 组测试用例，无法让从左数第 2 和第 3 个煎饼都朝同一面，因为任何一次翻转都会同时翻转它们。因此无法让所有煎饼都开心面朝上。

**数据范围**

- $1 \leq T \leq 100$。
- $S$ 中每个字符均为 + 或 -。
- $2 \leq K \leq S$ 的长度。

**小数据集（5 分，测试集 1 - 可见）**

- $2 \leq S$ 的长度 $\leq 10$。

**大数据集（10 分，测试集 2 - 隐藏）**

- $2 \leq S$ 的长度 $\leq 1000$。

由 ChatGPT 4.1 翻译

## 样例 #1

### 输入

```
3
---+-++- 3
+++++ 4
-+-+- 4```

### 输出

```
Case #1: 3
Case #2: 0
Case #3: IMPOSSIBLE```

# 题解

## 作者：HJH_2024 (赞：3)

## P13158 [GCJ 2017 Qualification] Oversized Pancake Flipper

[题目](https://www.luogu.com.cn/problem/P13158)
### 题目描述

给予一个长度为 $n$ 的由 `+` `-` 构成的字符串 $S$，与单次可操作区间长度（不能超出字符串 $S$）进行反转操作，知道 $S$ 全部为 `+`，求最小操作次数，如果不能输出`IMPOSSIBLE`。

### 分析
题目标签只有贪心，因此考虑贪心。

我们需要寻找 -，每找到一次就可以翻转一次，从左到右遍历，直到最后一个。

注意：本题是无后效性的，每次结束操作时，是对前面没有影响的。
### 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int t,k;
string s;
int work(){
	int len=s.length(),ret=0;//len: 字符串长度 ret:操作次数
	for(int i=0;i<len;i++){
		if(s[i]=='-'){
			ret++;
			if(i+k>len) continue;//如果铲子超出边界
			/*进行翻转操作*/
			for(int j=0;j<k&&j+i<len;j++){
				if(s[i+j]=='+') s[i+j]='-';
				else s[i+j]='+';
			}
		}
	}
	/*验证是否处理完成*/
	for(int i=0;i<=len;i++){
		if(s[i]=='-') return -1; 
	}
	return ret;
}
int main(){
	cin>>t;
	for(int i=1;i<=t;i++){
		s.clear();
		cin>>s>>k;
		printf("Case #%d: ",i);
		int p=work();
		if(p==-1){
			cout<<"IMPOSSIBLE\n";
		}else cout<<p<<'\n';
	}
	return 0;
}
```

---

## 作者：sonny2011 (赞：1)

[传送门](https://www.luogu.com.cn/problem/P13158)  
## 题目大意  
给出一个 $01$ 串，每次对 $k$ 个连续的数取反，求最少几次可以把这个串全变为 $1$。
## 思路  
一眼贪心。  
从前往后扫描这个串，每次遇到 $0$ 的时候就对这个数及其后面的 $k$ 个数进行一次取反，并记录次数，最后检查这个串中的数字是不是全为 $1$ 就可以了。  
因为每次都是对扫描到的位置的后面的位置进行取反，所以对前面已经全变为 $1$ 的位置不产生影响，所以可以证明这样做是可以得到最优解的。
## Code  
```cpp
#include<bits/stdc++.h>
using namespace std;
int cnt=0,k,a[1010];
string s;
void solve()
{
    cin>>s>>k;
    int l=s.size(),ans=0;
    for(int i=0;i<l;++i)a[i+1]=(s[i]=='+');//将字符串转存为01数组
    for(int i=1;i<=l-k+1;++i)
    {
        if(a[i]==0)//贪心寻找第一个为0的位置
        {
            ans++;
            for(int j=i;j<=i+k-1;++j)
            {
                a[j]=a[j]^1;//取反
            }
        }
    }
    cout<<"Case #"<<cnt<<": ";
    for(int i=1;i<=l;++i)
    {
        if(a[i]==0)
        {
            cout<<"IMPOSSIBLE\n";//特判无解
            return;
        }
    }
    cout<<ans<<'\n';
}
int main()
{
    std::ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);//卡常，可以缩小常数，但在这个题中用处不大
    int T;
    cin>>T;
    while(T--)
    {
        cnt++;
        solve();
    }
    return 0;
}
```

---

## 作者：dhy_2014 (赞：0)

[题目传送门](https://luogu.com.cn/problem/p13158)

## 题目大意
给了你一个 $01$ 串，你可以定一个长度刚好为 $k$ 的区间，对此区间内的所有数取反，问最少要取反几次。
## 思路
我们考虑贪心的做法，把这个 $01$ 串遍历一遍，如果当前数是 $0$，那么把 $i$ 到 $i+k-1$ 这个区间取反，以此类推，然而你改变后面的字符不会影响前面的字符，所以这种方案一定是最优的。

废话不多，上代码。

```cpp
#include<bits/stdc++.h>
using namespace std;
int t;
int k;
string s;
int main(){
    cin>>t;
    for(int o=1;o<=t;o++){
        int cnt=0;
        cin>>s>>k;
        int n=s.length();
        for(int i=0;i<=n-k;i++){//将i遍历到n-k 
            if(s[i]=='-'){ 
                cnt++;
                for(int j=i;j<=i+k-1;j++){//开始取反 
                    if(s[j]=='-'){
                        s[j]='+';
                    }
                    else{
                        s[j]='-';
                    }
                }
            }
        }
        cout<<"Case #"<<o<<": ";
        int flag=1;
        for(int i=0;i<n;i++){//最后再扫一遍，看看有没有无解 
            if(s[i]=='-'){
                flag=0;
            }
        }
        if(flag==0){
            cout<<"IMPOSSIBLE\n";
        }
        else{
            cout<<cnt<<'\n';
        }
    }
    return 0;
}
```

---

## 作者：4041nofoundGeoge (赞：0)

## 题目大意

给你一个 `-+` 串 $S$，请你操作字符串，每一次操作一个区间 $[i,i+n)(i+n\le \text{len }S)$，使其中 `+` 变 `-`，`-` 变 `+`，问最小操作次数使所有字符都为 `+`。

## 思路

考虑贪心。

寻找 `-` 并进行一次操作，直到全部字符变为 `+`。

证明：

由于翻转操作是从左到右进行的，翻转后的煎饼 $i$ 到 $i+K-1$ 的状态会被反转，但已经处理过的煎饼 $0$ 到 $i-1$ 的状态不会受到影响。满足无后效性的条件。

## 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
bool flag[1005];//观赏数组
int main(){
    int t;
    cin>>t;
    int q=t;
    while(t--){
        string s;
        int n;
        cin>>s>>n;
        int cnt=0;
        for(int i=0;i<s.size();i++){
            if(s[i]=='-'){
                for(int j=i;j<=i+n-1&&i+n<=s.size();j++){//坑
                    if(s[j]=='-')s[j]='+';
                    else s[j]='-';
                }
                cnt++;
            }
        }
        for(int i=0;i<s.size();i++){
            if(s[i]=='-'){
                cnt=-1;
                break;
            }
        }
        cout<<"Case #"<<q-t<<": ";
        if(cnt==-1)cout<<"IMPOSSIBLE\n";
        else cout<<cnt<<endl;
    }
    return 0;
}
```

---

