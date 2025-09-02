# Stages

## 题目描述

Natasha is going to fly to Mars. She needs to build a rocket, which consists of several stages in some order. Each of the stages is defined by a lowercase Latin letter. This way, the rocket can be described by the string — concatenation of letters, which correspond to the stages.

There are $ n $ stages available. The rocket must contain exactly $ k $ of them. Stages in the rocket should be ordered by their weight. So, after the stage with some letter can go only stage with a letter, which is at least two positions after in the alphabet (skipping one letter in between, or even more). For example, after letter 'c' can't go letters 'a', 'b', 'c' and 'd', but can go letters 'e', 'f', ..., 'z'.

For the rocket to fly as far as possible, its weight should be minimal. The weight of the rocket is equal to the sum of the weights of its stages. The weight of the stage is the number of its letter in the alphabet. For example, the stage 'a 'weighs one ton,' b 'weighs two tons, and' z' — $ 26 $ tons.

Build the rocket with the minimal weight or determine, that it is impossible to build a rocket at all. Each stage can be used at most once.

## 说明/提示

In the first example, the following rockets satisfy the condition:

- "adx" (weight is $ 1+4+24=29 $ );
- "ady" (weight is $ 1+4+25=30 $ );
- "bdx" (weight is $ 2+4+24=30 $ );
- "bdy" (weight is $ 2+4+25=31 $ ).

Rocket "adx" has the minimal weight, so the answer is $ 29 $ .

In the second example, target rocket is "belo". Its weight is $ 2+5+12+15=34 $ .

In the third example, $ n=k=2 $ , so the rocket must have both stages: 'a' and 'b'. This rocket doesn't satisfy the condition, because these letters are adjacent in the alphabet. Answer is -1.

## 样例 #1

### 输入

```
5 3
xyabd
```

### 输出

```
29```

## 样例 #2

### 输入

```
7 4
problem
```

### 输出

```
34```

## 样例 #3

### 输入

```
2 2
ab
```

### 输出

```
-1```

## 样例 #4

### 输入

```
12 1
abaabbaaabbb
```

### 输出

```
1```

# 题解

## 作者：YUYGFGG (赞：1)

思路：先对字符串排序，然后从头到尾枚举，如果相邻元素差大于 $1$ 则记录，否则跳过，当满足要求的元素够 $k$ 个时输出 $k$ ，如果不够则输出 $-1$ 。

code:

```cpp
#include<bits/stdc++.h>
#define fol(i,a,b) for(int i=a;i<=(b);i++)
#define bor(i,a,b) for(int i=a;i>=(b);--i)
using namespace std;
int main(){
    int n,k;
    ios::sync_with_stdio(false);
    cin.tie(0);
    string str;
    cin>>n>>k>>str;
    sort(str.begin(),str.end());
    int sum=str[0]-'a'+1;
    char tmp=str[0];
    int num=1;
    fol(i,1,n-1){
        if(num==k){
            break;
        }
        if(str[i]-tmp>1){
            num++;
            tmp=str[i];
            sum+=tmp-'a'+1;
        }
    }
    if(num==k){
        cout<<sum<<endl;
    }
    else{
        cout<<-1<<endl;
    }
    return 0;
}
```


---

## 作者：Cappuccino_mjj (赞：0)

## [题目传送门](https://www.luogu.com.cn/problem/CF1011A)
题目意思：

给你一个长度为 $n$ 的字符串 $a$，在这个字符串中选一个长度为 $k$ 的好串（好串标准是啥自己去题目里看吧），问这个好串的最小价值是多少。

---

思路：

贪心。
1. 首先我们将字符串 $a$ 里面的字符进行排序。
2. 因为要最小的价值，所以排好序后的 $a$ 的第一个字符是肯定要的，将它存进一个新的字符数组 $b$ 里面。
3. 遍历排好序后的 $a$，按照要求把符合的字符放进 $b$ 中，直到 $b$ 里面已经有了 $k$ 个字符。
4. 最后计算价值即可。

---

代码：
```cpp
#include<bits/stdc++.h>
using namespace std;
int k,n;
char a[100];
char b[100];
int cnt=1;
int main()
{
	cin>>n>>k;
	cin>>a+1;
	sort(a+1,a+1+n);
	b[cnt]=a[1];
	for(int i=2;i<=n;i++)
	{
		if(cnt==k)break;
		int x=b[cnt]-'a';
		int y=a[i]-'a'-1;
		if(y>x)
			b[++cnt]=a[i];
	}
	if(cnt!=k)
	{
		cout<<-1;
		return 0;
	}
	int ans=0;
	for(int i=1;i<=k;i++)
		ans=ans+(b[i]-'a'+1);
	cout<<ans;
	return 0;
}
```

---

完美撒花~

---

## 作者：1qaz234567pzy (赞：0)

### [原题传送门](https://www.luogu.com.cn/problem/CF1011A)


------------
### 思路：贪心

想要一个字符串的优秀成度越小，其字典序也就要越小。所以对原字符串进行从小到大排序，然后从左到右遍历，如果有在字母表上不连续的字母就将 $ans$ 加 $1$，把这个字母存起来。如果 $ans$ 小于 $k$ 的话，就输出 $-1$，否则就把可以选的字母的贡献最小的那 $k$ 个的贡献加起来就是答案了。


**贪心证明**：现有 $a$，$b$，$c$，$d$，如果我们一开始选 $a$，我们接下来就能选 $c$，但如果我们选 $b$，接下来就只能选 $d$，后面的选择也会受影响，就不是最优的了，证毕。





代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
string aaa;
int sh[100];
int  n,k;
int shu[1000];
int cnt;
int ans;
int main()
{
    cin>>n;
    cin>>k;
    cin>>aaa;
    for(int qq=0;qq<aaa.size();qq++)
    {
        sh[qq+1]=aaa[qq]-'a'+1;
    }
    sort(sh+1,sh+1+n);
    int last_=-1;
    for(int qq=1;qq<=n;qq++)
    {
        if(sh[qq]>=last_+2)
        {
            last_=sh[qq];
            shu[++cnt]=sh[qq];
        }
    }
 //   cout<<"OK\n"<<endl;
    if(k>cnt)//可选的字母数量不够
    {
        cout<<-1;
        return 0;
    }
    else
    {
        for(int qqq=1;qqq<=k;qqq++)
        {
            ans+=shu[qqq];
        }
    }
    cout<<ans;
    return 0;
}

```

---

## 作者：xiaofeng_and_xiaoyu (赞：0)

贪心经典题。

对于遇到的每一个字符，由于差要在 $1$ 以上，所以每个字符只用存一次。

当这个字符被取出时，由于差要在 $1$ 以上，所以直接 $\verb!j++!$ 就可以了。

总复杂度 $O(n\min(\frac{27}{2},m))$，可以过本题。

~~实际上时空（当时）排第二~~

代码如下：

```cpp
#include<bits/stdc++.h>
using namespace std;
bool t[27];
int main(){
    int x,y,z=0,ans=0;
    char a;
    cin>>x>>y;
    for(int i=0;i<x;i++){
    	cin>>a;
    	t[a-'a'+1]=1;
	}
   	for(int j=1;j<27&&y;j++){
    	if(t[j]){
    		ans+=j;
    		j++;
    		y--;
		}
	}
	if(y){
		cout<<-1;
	}else{
		cout<<ans;
	}
    return 0;
}
```


------------
PS：第一次写时间复杂度，不知道对不对啊QAQ

因为取一个数就隔一个，所以是 $27\div2$ （准确来讲还该 $+1$ ）

---

## 作者：Yang_OIer (赞：0)

## 这是一道贪心题

### 贪心策略:


#### 只要取字典序最小的字符。它的价值就小。


------------

原因：当我们取到 `a` 时，可以保证对后面的字母可以使用。例如：有 `a`,`b`,`c` 三个字母，若选 `a`,`c` 同样可选，选 `b` 则不行，后面的 `b`，`c`，`d` 等等也同理。
我们用动态数组记录所有能选的字符，从头开始输出 `k` 个即可。


------------

## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int n,k,l=0,ans,a[51];
char x;
int main(){
	vector<int>v;
	cin>>n>>k;
	for(int i=1;i<=n;++i){
		cin>>x;
		a[i]=x-'a'+1;
	}
	sort(a+1,a+n+1);
	int l=-1;
	for(int i=1;i<=n;++i)
		if(a[i]>=l+2){
			v.push_back(a[i]);
			l=a[i];
		}
	if(v.size()<k)
		cout<<'-1'<<endl;
	else{
		for(int i=0;i<k;++i)
			ans+=v[i];
		cout<<ans;
	}
	return 0;
}
```


---

## 作者：oimaster (赞：0)

根据基本贪心，我们如果能取得 `a` 就会取 `a`，能取当前字符就不会取字母表后一个字符。

感性理解一下这个贪心。

- 当我们取到 `a` 时，可以保证价值得到最低化，因为 `a` 的代价比任何一个字母表后面的字符的代价少，所以能选 `a` 就不会选 `b`。能选 `b` 就不会选 `c`。
- 当我们取到 `a` 时，可以保证对后面的字母尽可能地利用，因为如果可以选择 `a`、`b`、`c`，当我们这一步选择 `a` 时，`c` 可以选。当我们选择 `b` 时，`c` 就不能选了。所以能选 `a` 就不会选 `b`。

后面的 `b`，`c`，`d` 等等也同理。考虑代码实现，我们可以用 `std::vector` 记录所有能选的字符，然后从头开始输出 $k$ 个即可。当然，如果向量的大小小于 $k$，就无解。

时间复杂度：$\text{O}(n\log n)$。之所以有 $\log$ 是因为我们需要排序。

```cpp
#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;
int main(){
	int n;
	int k;
	cin>>n>>k;
	int a[n+1];
	for(int i=1;i<=n;++i){
		char x;
		cin>>x;
		a[i]=x-'a'+1;
	}
	sort(a+1,a+n+1);
	vector<int>v;
	int last=-1;
	for(int i=1;i<=n;++i)
		if(a[i]>=last+2){
			v.push_back(a[i]);
			last=a[i];
		}
	if(v.size()<k){
		cout<<-1<<endl;
		return 0;
	}
	int sum=0;
	for(int i=0;i<k;++i)
		sum+=v[i];
	cout<<sum<<endl;
}
```

---

## 作者：小闸蟹 (赞：0)

```cpp
// 贪心题，首先将字符串按从小到大排序，然后从前往后取字符，只要不是连续的字符就可以取
#include <iostream>
#include <string>
#include <algorithm>

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n, k;
    std::cin >> n >> k;

    std::string Str;
    std::cin >> Str;

    std::sort(Str.begin(), Str.end());

    int Ans = Str[0] - 'a' + 1; // 头字符肯定可以取，先取一个看看
    --k;

    if (k == 0)
    {
        std::cout << Ans << std::endl;
    }
    else
    {
        auto Pre = Str[0];  // 记录上一次取得的字符
        for (int i = 1; i < n; ++i)
        {
            if (Str[i] - Pre > 1)   // 不连续则可以取
            {
                Ans += Str[i] - 'a' + 1;
                Pre = Str[i];

                if (--k == 0)
                {
                    std::cout << Ans << std::endl;

                    return 0;
                }
            }
        }

        std::cout << -1 << std::endl;
    }

    return 0;
}
```

---

