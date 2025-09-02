# [ABC320C] Slot Strategy 2 (Easy)

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc320/tasks/abc320_c

> この問題は G 問題の簡易版です。

$ 3 $ 個のリールからなるスロットがあります。  
 $ i $ 番目のリールの配列は文字列 $ S_i $ によって表されます。ここで、$ S_i $ は数字のみからなる長さ $ M $ の文字列です。

それぞれのリールには対応するボタンがついています。高橋君は各非負整数 $ t $ について、スロットが回り始めてからちょうど $ t $ 秒後にボタンを $ 1 $ つ選んで押す、または何もしないことができます。  
 スロットが回り始めてから $ t $ 秒後に $ i $ 番目のリールに対応するボタンを押すと、$ i $ 番目のリールは $ S_i $ の $ (t\ \bmod\ M)+1 $ 文字目を表示して止まります。  
 ただし、$ t\ \bmod\ M $ で $ t $ を $ M $ で割ったあまりを表します。

高橋君は全てのリールを止めた上で、表示されている文字が全て同じであるようにしたいです。  
 高橋君が目標を達成できるように全てのリールを止めるまでに、スロットが回り始めてから最小で何秒かかるかを求めてください。  
 そのようなことが不可能であればそのことを報告してください。

## 说明/提示

### 制約

- $ 1\ \leq\ M\ \leq\ 100 $
- $ M $ は整数
- $ S_i $ は数字のみからなる長さ $ M $ の文字列
 
### Sample Explanation 1

高橋君は次のようにそれぞれのリールを止めることでスロットが回り始めてから $ 6 $ 秒後にリールに表示される文字を `8` で揃えることができます。 - スロットの回転開始から $ 0 $ 秒後に $ 2 $ 番目のリールに対応するボタンを押します。$ 2 $ 番目のリールは $ S_2 $ の $ (0\ \bmod\ 10)+1=1 $ 文字目である `8` を表示して止まります。 - スロットの回転開始から $ 2 $ 秒後に $ 3 $ 番目のリールに対応するボタンを押します。$ 3 $ 番目のリールは $ S_3 $ の $ (2\ \bmod\ 10)+1=3 $ 文字目である `8` を表示して止まります。 - スロットの回転開始から $ 6 $ 秒後に $ 1 $ 番目のリールに対応するボタンを押します。$ 1 $ 番目のリールは $ S_1 $ の $ (6\ \bmod\ 10)+1=7 $ 文字目である `8` を表示して止まります。 $ 5 $ 秒以下で全てのリールに表示されている文字を揃える方法はないため、$ 6 $ を出力します。

### Sample Explanation 2

全てのリールを止めた上で、表示されている文字を揃える必要がある事に注意してください。

### Sample Explanation 3

表示されている文字が全て同じであるようにリールを止めることはできません。 このとき `-1` を出力してください。

## 样例 #1

### 输入

```
10
1937458062
8124690357
2385760149```

### 输出

```
6```

## 样例 #2

### 输入

```
20
01234567890123456789
01234567890123456789
01234567890123456789```

### 输出

```
20```

## 样例 #3

### 输入

```
5
11111
22222
33333```

### 输出

```
-1```

# 题解

## 作者：2c_s (赞：5)

[题目传送门](https://www.luogu.com.cn/problem/AT_abc320_c)

## 题目大意

给定长度为 $N$ 的三个**横向**老虎机转盘，在开始转动后可以在**不同的**时间停下不同的转盘。转盘从右向左转动。求把所有转盘的首位统一的最小用时，如果不能统一就输出 ``-1``。

## 思路

考虑用贪心的做法解决本题。

读入数据后进行预处理。因为在能统一的最不利情况下是每个转盘都只出现同样的数字一次，且在同一位置。这时候我们**最多**只需要转动 $3$ 圈就能将转盘的首位统一。所以我们将每个转盘列数翻 $3$ 倍，以做到转动三圈的效果。

之后三重循环找三个老虎机转盘有没有统一的一位。如果有同样的一位并且位置不相等，就说明能在**不同时间**停下后，$3$ 个转盘的首位是统一的。这时候我们记录这三个位置的最大值（也就是最晚停下的那个转盘的记录时间）。

最后输出记录的数的最小值。如果没记录过就输出 ``-1`` 代表无论怎么停下这三个转盘，都不能找到一个统一的位置，结束程序。

### 注意事项

- 在把转盘列数翻 $3$ 倍的时候，别忘把记录列数的 $N$ 也 $\times 3$。

- 可以将记录停下时间最小值的变量赋初始值 $10^9$，做到判断有没有被记录过的效果。

## AC 代码

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,ans=1e9;
string a,b,c;
int main(){
	cin>>n>>a>>b>>c;
	a=a+a+a;
	b=b+b+b;
	c=c+c+c;
	n=n+n+n;
	for(int i=0;i<n;++i){//遍历第一个转盘。
		for(int j=0;j<n;++j){//遍历第二个转盘。
			for(int k=0;k<n;++k){//遍历第三个转盘。
				if(a[i]==b[j]&&b[j]==c[k]&&i!=j&&j!=k&&i!=k){//找到相等的且不在同一位置的一位。
					ans=min(ans,max({i,j,k}));//取最大值的最小值。
				}
			}
		}
	}
	if(ans==1e9)cout<<-1;//如果没被记录过。
	else cout<<ans;
	return 0;
}
```

[AC 记录](https://www.luogu.com.cn/record/124936712)

---

## 作者：__Dist__ (赞：2)

### 题目链接

[Luogu](https://www.luogu.com.cn/problem/AT_abc320_c) | [AtCoder](https://atcoder.jp/contests/abc320/tasks/abc320_c)

### 思路讲解

提供一个比较麻烦的方法：

分别把每个卷轴标号为 $1\sim 3$。由于，我们停止每个卷轴的顺序十分重要，关乎总时间，而数据范围较小，我们可以枚举每个符合要求的排列，再从中取最小值即可。

符合要求的排列如下：

```
1 2 3
1 3 2
2 1 3
2 3 1
3 1 2
3 2 1
```

然后大体按照这个思路写代码就行了。

### Code

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
signed main()
{
    int m;
    cin>>m;
    string a,b,c;
    cin>>a>>b>>c;
    int ans=1e18;
    for(int i=0;i<m;i++)
    {
        int p=-1;
        for(int k=1,time=0;k<4;k++)
        {
            bool f=false;
            for(int j=0;j<m;j++,time++)
            {
                if(b[j]==a[i]&&time!=i)
                {
                    p=time;
                    f=true;
                    break;
                }
            }
            if(f) break;
        }
        if(p==-1) continue;
        int q=-1;
        for(int k=1,time=0;k<4;k++)
        {
            bool f=false;
            for(int j=0;j<m;j++,time++)
            {
                if(c[j]==a[i]&&time!=i&&time!=p)
                {
                    q=time;
                    f=true;
                    break;
                }
            }
            if(f) break;
        }
        if(q==-1) continue;
        int ans1=min(ans,max(p,max(q,i)));
        
        //1 2 3
        
        p=-1;
        for(int k=1,time=0;k<4;k++)
        {
            bool f=false;
            for(int j=0;j<m;j++,time++)
            {
                if(c[j]==a[i]&&time!=i)
                {
                    p=time;
                    f=true;
                    break;
                }
            }
            if(f) break;
        }
        if(p==-1) continue;
        q=-1;
        for(int k=1,time=0;k<4;k++)
        {
            bool f=false;
            for(int j=0;j<m;j++,time++)
            {
                if(b[j]==a[i]&&time!=i&&time!=p)
                {
                    q=time;
                    f=true;
                    break;
                }
            }
            if(f) break;
        }
        if(q==-1) continue;
        int ans2=max(p,max(q,i));
        //1 3 2
        ans=min(min(ans,ans1),ans2);
    }
    for(int i=0;i<m;i++)
    {
        int p=-1;
        for(int k=1,time=0;k<4;k++)
        {
            bool f=false;
            for(int j=0;j<m;j++,time++)
            {
                if(a[j]==b[i]&&time!=i)
                {
                    p=time;
                    f=true;
                    break;
                }
            }
            if(f) break;
        }
        if(p==-1) continue;
        int q=-1;
        for(int k=1,time=0;k<4;k++)
        {
            bool f=false;
            for(int j=0;j<m;j++,time++)
            {
                if(c[j]==b[i]&&time!=i&&time!=p)
                {
                    q=time;
                    f=true;
                    break;
                }
            }
            if(f) break;
        }
        if(q==-1) continue;
        int ans1=min(ans,max(p,max(q,i)));
        
        //2 1 3
        
        p=-1;
        for(int k=1,time=0;k<4;k++)
        {
            bool f=false;
            for(int j=0;j<m;j++,time++)
            {
                if(c[j]==b[i]&&time!=i)
                {
                    p=time;
                    f=true;
                    break;
                }
            }
            if(f) break;
        }
        if(p==-1) continue;
        q=-1;
        for(int k=1,time=0;k<4;k++)
        {
            bool f=false;
            for(int j=0;j<m;j++,time++)
            {
                if(a[j]==b[i]&&time!=i&&time!=p)
                {
                    q=time;
                    f=true;
                    break;
                }
            }
            if(f) break;
        }
        if(q==-1) continue;
        int ans2=max(p,max(q,i));
        //2 3 1
        ans=min(min(ans,ans1),ans2);
    }
    for(int i=0;i<m;i++)
    {
        int p=-1;
        for(int k=1,time=0;k<4;k++)
        {
            bool f=false;
            for(int j=0;j<m;j++,time++)
            {
                if(a[j]==c[i]&&time!=i)
                {
                    p=time;
                    f=true;
                    break;
                }
            }
            if(f) break;
        }
        if(p==-1) continue;
        int q=-1;
        for(int k=1,time=0;k<4;k++)
        {
            bool f=false;
            for(int j=0;j<m;j++,time++)
            {
                if(b[j]==c[i]&&time!=i&&time!=p)
                {
                    q=time;
                    f=true;
                    break;
                }
            }
            if(f) break;
        }
        if(q==-1) continue;
        int ans1=min(ans,max(p,max(q,i)));
        
        //3 1 2
        
        p=-1;
        for(int k=1,time=0;k<4;k++)
        {
            bool f=false;
            for(int j=0;j<m;j++,time++)
            {
                if(b[j]==c[i]&&time!=i)
                {
                    p=time;
                    f=true;
                    break;
                }
            }
            if(f) break;
        }
        if(p==-1) continue;
        q=-1;
        for(int k=1,time=0;k<4;k++)
        {
            bool f=false;
            for(int j=0;j<m;j++,time++)
            {
                if(a[j]==c[i]&&time!=i&&time!=p)
                {
                    q=time;
                    f=true;
                    break;
                }
            }
            if(f) break;
        }
        if(q==-1) continue;
        int ans2=max(p,max(q,i));
        ans=min(min(ans,ans1),ans2);
        //3 2 1
    }
    cout<<(ans==1e18?-1:ans);
    return 0;
}
```

---

## 作者：AC_love (赞：1)

我敢说全网和我做法相同的人不超过十个（乐

此题几乎所有题解做法都是 $O(m^3)$ 的暴力枚举，前面还带着一个 $6$ 倍常数，在 $m \le 100$ 的时候还能勉强跑一跑，然而一旦 $m$ 稍微大一点，很容易就能卡到 TLE。

那么我们应该怎么办才能优化复杂度呢？

dalao1：我觉得应该二分答案！

dalao2：直接二分图匹配跑匈牙利就行！

AClove：杀鸡焉用屠龙宝刀啊喂！

其实不需要任何算法知识，只要 $O(m)$ 从头到尾枚举一遍就行了。

------------

首先我们要考虑对这个问题进行转化：

注意到：如果我们要得到三个一样的数字，这个数字一定在三个轮盘里出现过且出现在不同位置。

因此我们只需要开一个桶记录每个数字在每个轮盘中出现的情况就行了。

然而这样也会有一个问题，我们开桶来存的话，如何确保三个数出现的位置不一样呢？

其实思路很简单。

如果某个位置上，三个轮盘互不相同，那么很显然，这时候每个数都可以被加入各自对应的桶中。

而如果有两个数相同，另外一个不同，那么不同的那个数可以被存入桶中，而相同的数不能直接存。

如果三个数相同，那么都没法直接存。

为什么呢？

很显然，如果你把相同的数直接全部存进对应的桶中的话，判断时就会认为你可以同时取得这些数，然而实际上是不可以的。

所以：不同的数可以直接存，相同的数可以暂时存到另一个桶中，我们一会儿再处理。

那么我们思考一个问题，第二个桶里的内容能否转移到第一个桶里呢？

显然是可以的。

如果一个数在第二个桶出现了两次，那么第一次可以取另一个数，第二次再来取这个数，因此这个数一定是可以被取到的。

所以只要第二个桶里的数 $\ge 2$，我们就可以把第二个桶里的数转移到第一个桶。

那么符合题意的情况大概就是这样的：

1. 三个数都在第一个桶出现过。
2. 两个数在第一个桶出现过，另一个在第二个桶出现过。

注意，每次循环开始的时候都只应该考虑本次出现的三个数是否已经符合题意，而不能从 $0$ 到 $9$ 遍历一遍，这样做的原因不仅仅是减小常数，还能保证我们代码的正确性。

具体原因如下：

有人可能有质疑：如果三个数都是相同的，那即使第二个桶里的数 $= 2$，我们也未必取得到啊。

同时他们会给出这样一组 hack 数据：

```
1
2
2
2
```

显然，如果我们按照之前的逻辑运行的话，我们给出的答案会是 $2$，然而正解显然是 $3$。

但我考虑到了这种情况，其实有一个很简单的解决方法，每次循环时先判断合法与否，然后我们再进行第二个桶到第一个桶的转移。

有人说：这有用吗？

有用。

我们发现，如果我们先判断合法与否，再进行转移的话，给出的答案就是 $3$，恰好是正解。

这是瞎猫碰上死耗子吗？

其实并不是。

我们可以分析一下为什么先判断合法再进行转移是正解。

我们每次循环开始时只会判断这次出现的数里有没有满足题意的，因此即使我们三个数都在各自的第一个桶里出现过，我们也不能直接判断此时满足题意（这就是为什么我刚才强调不能从 $0$ 到 $9$ 遍历一遍的原因）。

只有当这个数再次出现的时候，我们才会判断到这个数在第一个桶出现过，我们此时输出答案，一定是正确的。

代码实现：https://atcoder.jp/contests/abc320/submissions/45609545

（我的代码比较长，因为我把 if 全都分开写了，所以这里不贴代码了，如果已经懂了可以自己写一下，不太理解可以点进去看看，看完代码还是不懂可以在下方评论问我）

---

## 作者：kimidonatsu (赞：1)

# AT_abc320_c [ABC320C] Slot Strategy 2 (Easy) 题解

数据范围只有 $1 \leq M \leq 100$。

考虑暴力枚举，需注意，如果转盘转动了三次还不能匹配数字那么就永远无法匹配，所以枚举到 $3 \times M - 1$ 即可。

```cpp
#include <bits/stdc++.h>

void solve() {
	int M;
    std::cin >> M;
    int N = 3;
    std::vector<std::string> S(N);
    for (int i = 0; i < N; i++) {
        std::cin >> S[i];
    }
    int INF = std::numeric_limits<int>::max();
    int ans = INF;
    for (int i = 0; i < N * M; i++) {
        for (int j = 0; j < N * M; j++) {
            for (int k = 0; k < N * M; k++) {
                if (i != j && i != k && j != k && S[0][i % M] == S[1][j % M] && S[1][j % M] == S[2][k % M]) {
                    ans = std::min(ans, std::max({i, j, k}));
                }
            }
        }
    }
    std::cout << (ans < INF ? std::to_string(ans) : "-1") << std::endl;
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr), std::cout.tie(nullptr);

	solve();
	return 0;
}

```


---

## 作者：Dream_poetry (赞：1)

### 思路：
我们发现，数据范围是很水的，$M$ 长度小于等于 $100$，而又只要求 $3$ 个字符相等即可，所以可以尝试暴力解决。

为了避免出现 $M=1$ 这种情况，我们先将 $M \times 3$，再将 $a$，$b$，$c$ 三个字符串和自己粘贴两次。

接下来暴力搜索，当 $b$ 和 $c$ 中都第一次出现了 $a_i$ 这个字符时，$ans$ 即为这个字符在 $b$ 或 $c$ 中第一次出现这个字符的下标。

不断将 $ans$ 取 $\min$，最后输出。

我们将 $ans$ 初始设为极大值，如果 $ans$ 到最后还是极大值，输出 $-1$。

### 代码：
~~~cpp
#include<bits/stdc++.h>
using namespace std;
int n,ans=1e9;
string a,b,c;
int main(){
	cin>>n>>a>>b>>c;
	a=a+a+a,b=b+b+b,c=c+c+c;
	n=n+n+n;
	for(int i=0;i<n;++i){
		for(int j=0;j<n;++j){
			for(int k=0;k<n;++k){
                if(a[i]==b[j]&&b[j]==c[k]&&i!=j&&j!=k&&i!=k){
					ans=min(ans,max({i,j,k}));
				}
			}
		}
	}
	if(ans==1e9) cout<<-1;
	else cout<<ans;
	return 0;
}
~~~

---

## 作者：CommunismFighter (赞：1)

# [传送门](https://atcoder.jp/contests/abc320/tasks/abc320_c)

观察样例可以发现，最后相同的一定是 $0\sim9$ 之间的某个数字。

所以，我们预处理出每个数字在每一行中出现的次数和位置，之后直接依次枚举数字 $i$ 在第 $j(j=1,2,3)$ 行出现的位置，记为 $now_{i}$。

可以发现：
- 数字 $i$ 在这三行的位置 $nw_{i}$ 都不相同时，一定可以在第一轮内就被找完。

- 如果有两个位置相同，因为同一时间内只能按下一个按钮。那么其中一个位置对应的时间 $t = t+M$。

- 如果三个位置都相同，那么时间 $t = t+2M$。

对答案的贡献就是三个位置对应的时间的最大值。

时间复杂度 $O(n^3)$，且 $n$ 大概率跑不满，而且常数小于官方题解的延长 $n$ 的做法，可以通过本题（~~实际跑的比官方题解要快~~）。

```cpp
// LUOGU_RID: 124936646
#include<bits/stdc++.h>
#define int long long
#define mian main
#define rg register int 
using namespace std;
const int N = 105;
int len,ps[5][15][1005],times[5][15],ans = LONG_LONG_MAX;
char s[5][N];
signed mian(){
	scanf("%lld",&len);
	for(int i=0;i<3;++i) scanf("%s",s[i]);
	for(int i=0;i<3;++i){
		for(int j=0;j<len;++j){
			ps[i][s[i][j]-'0'][++times[i][s[i][j]-'0']] = j;
		}		
	}
	for(int i=0;i<10;++i){
		for(int j=1;j<=times[0][i];++j){
			int nw1 = ps[0][i][j];
			for(int z=1;z<=times[1][i];++z){
				int nw2 = ps[1][i][z];
				for(int q=1;q<=times[2][i];++q){
					int nw3 = ps[2][i][q];
					if(nw1==nw2 && nw1==nw3 && nw2==nw3){
						ans = min(ans,nw1+len+len);
					}else{
						if(nw1==nw2){
							ans = min(ans,max(nw1,max(nw2+len,nw3)));
						}else if(nw1==nw3){
							ans = min(ans,max(nw1,max(nw2,nw3+len)));
						}else if(nw2==nw3){
							ans = min(ans,max(nw1,max(nw2,nw3+len)));
						}else{
							ans = min(ans,max(nw1,max(nw2,nw3)));
						}
					}
				}
			}
		}		
	}
	if(ans==LONG_LONG_MAX){
		puts("-1");
		return 0;
	}
	printf("%lld\n",ans);
	return 0;
}
```


---

## 作者：heyx0201 (赞：0)

# Slot Strategy 2 (Easy) 题解
## 题目简述
> 给定 $3$ 个长度为 $m$ 的老虎机转盘，转动过后三个转盘分别可以在**不同的时间**停下，求停下时所有转盘都显示相同数字的最小时间。

## 思路
由于这题 $m \le 100$，数据较水，所以可以先把每个数列都复制 $2$ 遍，因为最坏情况下是每个转盘都只出现一样的数字一次，而且在同一个位置，这时最多转 $3$ 圈就可以把首位统一。

$3$ 重循环枚举位置，如果 $3$ 个位置不相等，且数字一样，那么就更新答案，答案为三个位置中的最大值。

最后如果答案还是设定的初始值，那么输出 `-1`。
## Accepted Code
[Accepted Record](https://www.luogu.com.cn/record/124976724)
```cpp
#include<iostream>
#include<algorithm>
#include<climits>

using namespace std;

int m,ans = INT_MAX;
string a,b,c;

int main(){
  cin >> m >> a >> b >> c;
  a += a + a, b += b + b, c += c + c;
  for (int i = 1; i <= 3 * m; i++){
    for (int j = 1; j <= 3 * m; j++){
      for (int k = 1; k <= 3 * m; k++){
        if (i == j || j == k || i == k){
          continue;
        }
        if (a[i - 1] == b[j - 1] && b[j - 1] == c[k - 1] && a[i - 1] == c[k - 1]){
          ans = min(ans,max({i, j, k}) - 1);
        }
      }
    }
  }
  if (ans == INT_MAX){
    ans = -1;
  }
  cout << ans;
  return 0;
}
```

---

## 作者：_zzzzzzy_ (赞：0)

# 思路

这里主要就是把题目里面不能同时按读出来就很简单了。

我们考虑枚举三个相等的位置。

我们想一下如果三个位置相等，那么我们想要把他转到第一个就要等两个周期，然后取最大的就会是 $2m+i$。

然后考虑两个相等的，这就是等一个周期。

然后都不相等的肯定是按顺序取，不用等，那么就会是三个里面的最大值。

```cpp
#include <bits/stdc++.h>
#define rep(i, l, r) for (int i = (l); i <= (r); i++)
#define per(i, l, r) for (int i = (l); i >= (r); i--)
#define Debug(...) fprintf(stderr,__VA_ARGS__)
using namespace std;
using i64 = long long;
const int maxn = 1000000;
char a[maxn], b[maxn], c[maxn];
int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    
    int m, ans = INT_MAX;
    cin >> m >> (a + 1) >> (b + 1) >> (c + 1);
    rep(i, 1, m) {
        rep(j, 1, m) {
            rep(k, 1, m) {
                if (a[i] == b[j] && b[j] == c[k]) {
                    if (i == j && j == k) {
                        ans = min(ans, m * 2 + k);
                    } else if (i == j) {
                        ans = min(ans, m + i);
                    } else if (i == k) {
                        ans = min(ans, m + i);
                    } else if (j == k) {
                        ans = min(ans, m + j);
                    } else {
                        ans = min(ans, max(i, max(j, k)));
                    }
                }
            }
        }
    }
    if (ans == INT_MAX) {
        cout << -1 << "\n";
    } else {
        cout << ans - 1 << "\n";
    }
    return 0;
}
```

---

## 作者：__Emerald__ (赞：0)

这题通过第二个样例可以得到高桥不能同时按多次按钮，所以时间可能大于等于 $M$。（第二个样例是在第 $0$ 秒，第 $10$ 秒，第 $20$ 秒按下按钮的）

所以输出的范围是 $0$ 到 $3M-1$。（包括 $0$ 和 $3M-1$）

题目理解了，通过起来就简单了。

# AC Code 1:
```
#include <bits/stdc++.h>
using namespace std;
int m,ans = 500;
string s[5];
int main(){
	cin >> m;
	for (int i = 1;i <= 3;i++) cin >> s[i];
	for (int i = 0;i < 3 * m;i++) for (int j = 0;j < 3 * m;j++){
		if (i == j) continue;
		for (int k = 0;k < 3 * m;k++){
			if  (k == i || k == j) continue;
			if (s[1][i % m] == s[2][j % m] && s[2][j % m] == s[3][k % m]) ans = min(ans,max(i,max(j,k)));
		}
	}
	cout << (ans == 500? -1 : ans);
	return 0;
}
```
用时 100ms。
# AC Code 2:
```
#include <bits/stdc++.h>
using namespace std;
int m,ans = 500;
string s[5];
int main(){
	cin >> m;
	for (int i = 1;i <= 3;i++) cin >> s[i];
	s[1] = s[1] + s[1] + s[1],s[2] = s[2] + s[2] + s[2],s[3] = s[3] + s[3] + s[3];
	for (int i = 0;i < 3 * m;i++) for (int j = 0;j < 3 * m;j++){
		if (i == j) continue;
		for (int k = 0;k < 3 * m;k++){
			if  (k == i || k == j) continue;
			if (s[1][i] == s[2][j] && s[2][j] == s[3][k]) ans = min(ans,max(i,max(j,k)));
		}
	}
	cout << (ans == 500? -1 : ans);
	return 0;
}
```
用时 21ms。

---

## 作者：TempestMiku (赞：0)

- [AT_abc320_c [ABC320C] Slot Strategy 2 (Easy)](https://www.luogu.com.cn/problem/AT_abc320_c)

题目大意：

这个问题是G问题的简易版。

有一个老虎机，你可以停止一个插槽并花费 $1$ 时间，但是其他没有停止的插槽不会停止转动。问你三个插槽都相同最小花费的时间。


我们可以直接三层循环暴力，时间复杂度 $\Theta\left(n^3\right)$。

- 如果 $a=b=c$，那么答案就是 $2\times n+a$。因为需要多转两圈到达 $a$ 的下标。


- 如果其中两个值相同，比如 $a=b$，那么答案就是 $n+a$。因为需要多转一圈到达 $a$ 的下标。

- 如果 $a \ne b\ \text{且}\ a\ne c\ \text{且}\ b\ne c$，那么答案就是 $\max{\{a,b,c\}}$。因为需要小于一圈到达 $\max{\{a,b,c\}}$ 的下标。



```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
namespace Testify{
    inline int read(){
        int f(1),x(0);
        char ch=getchar();
        for(;!isdigit(ch);ch=getchar()) if(ch=='-') f=-1;
        for(;isdigit(ch);ch=getchar()) x=(x<<1)+(x<<3)+(ch^48);
        return f*x;
    }
    inline void Write(int x){
        if(x>9) Write(x/10);
        putchar(x%10+48);
    }
    inline void write(int x){
        if(x<0) putchar('-'),x=-x;
        Write(x);
        putchar('\n');
    }
}
using namespace Testify;
int n;
const int N=105;
int A[N],B[N],C[N];
string aaa,bbb,ccc;
int SATELLITE=LONG_LONG_MAX;
signed main(void){
    n=read();
    cin>>aaa>>bbb>>ccc;
    for(register int i=0;i<n;i++){
        A[i+1]=aaa[i];
        B[i+1]=bbb[i];
        C[i+1]=ccc[i];
    }
    for(register int i=1;i<=n;i++){
        for(register int j=1;j<=n;j++){
            for(register int k=1;k<=n;k++){
                if(A[i]==B[j]&&A[i]==C[k]){
                    int aa=i,bb=j,cc=k;
                    int sum;
                    if(aa==bb&&bb==cc){
                        sum=(2*n+aa);
                    }
                    else if(aa==bb){
                        sum=(aa+n);
                    }
                    else if(bb==cc){
                        sum=(bb+n);
                    }
                    else if(aa==cc){
                        sum=(aa+n);
                    }
                    else{
                        sum=max({aa,bb,cc});
                    }
                    SATELLITE=min(SATELLITE,sum-1);
                }
            }
        }
    }
    write(SATELLITE==LONG_LONG_MAX?-1:SATELLITE);
    return 0;
}
```

完结撒花

---

## 作者：白简 (赞：0)

### 题目大意
给定一个正整数 $m$ 和三个卷轴，卷轴第一位为初始位置。

考虑在第 $t_1,t_2,t_3$ 秒停下三个卷轴，要求满足 $t_1,t_2,t_3$ 互不相等（不能同时停下多个卷轴）。卷轴会循环转。

### 思路
由于 $m \leq 100$，我们可以直接枚举，考虑判断 $t_1,t_2,t_3$ 互不相等。

```cpp
#include <bits/stdc++.h>

using namespace std;

int m;

string st[5];

int ans = INT_MAX;

int main() {
    cin >> m;
    for(int i = 1;i <= 3; i++)
        cin >> st[i];
    
    for(int i = 0;i < 5 * m; i++) {
        for(int j = 0;j < 5 * m; j++) {
            for(int k = 0;k < 5 * m; k++) {
                if(st[1][i % m] == st[2][j % m] && st[2][j % m] == st[3][k % m]) {
                    if(i != j && j != k && i != k) {
                        ans = min(ans,max(i,max(j,k)));
                    }
                }
            }
        }
    }

    if(ans != INT_MAX)
        cout << ans << endl;
    else
        cout << "-1" << endl;
    return 0;
}
```

---

## 作者：muzqingt (赞：0)

## [ABC320C] Slot Strategy 2 (Easy) 题解

### 题意

>给定三个卷轴，每秒钟卷轴会向左边滚动一格。
>
>每秒钟都可以选择停下某一个卷轴或者什么都不干。
>
>要求停下时所有卷轴所示数字相同。
>
>问最短能够达成的时间。

### 思路

我们发现，想要数字相同时间不同，某一个数字必须至少在三个不同的时间出现。我们考虑把字符串复制成 $4$ 倍，数字就至少出现了 $4$ 次，符合条件。并且时间就可以作为下标使用。枚举三个下标就可以找到最小的满足答案的解。

### code

```cpp

#include<iostream>
#include<cstdio>
#include<string>
using namespace std;
string s1,s2,s3;
int main(){
    int n,an=1e9;
    scanf("%d",&n);
    cin>>s1>>s2>>s3;
    s1+=s1;
    s2+=s2;
    s3+=s3;
    s1+=s1;
    s2+=s2;
    s3+=s3;
    for(int i=0;i<4*n;i++){
        for(int j=0;j<4*n;j++){
            for(int k=0;k<4*n;k++){
                if(i!=j&&j!=k&&i!=k&&s1[i]==s2[j]&&s2[j]==s3[k]){
                    //cout<<i<<" "<<j<<" "<<k<<"\n";
                    an=min(an,max(max(i,j),k));
                }
            }
        }
    }
    if(an==1e9) cout<<"-1"<<endl;
    else 
    cout<<an<<"\n";
    return 0;
}

```

---

