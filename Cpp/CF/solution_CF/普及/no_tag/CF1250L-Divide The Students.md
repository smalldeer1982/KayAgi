# Divide The Students

## 题目描述

A group of students has recently been admitted to the Faculty of Computer Sciences at the Berland State University. Now the programming teacher wants to divide them into three subgroups for practice sessions.

The teacher knows that a lot of programmers argue which language is the best. The teacher doesn't want to hear any arguments in the subgroups, so she wants to divide the students into three subgroups so that no pair of students belonging to the same subgroup want to argue.

To perform this division, the teacher asked each student which programming language he likes. There are $ a $ students who answered that they enjoy Assembler, $ b $ students stated that their favourite language is Basic, and $ c $ remaining students claimed that C++ is the best programming language — and there was a large argument between Assembler fans and C++ fans.

Now, knowing that Assembler programmers and C++ programmers can start an argument every minute, the teacher wants to divide the students into three subgroups so that every student belongs to exactly one subgroup, and there is no subgroup that contains at least one Assembler fan and at least one C++ fan. Since teaching a lot of students can be difficult, the teacher wants the size of the largest subgroup to be minimum possible.

Please help the teacher to calculate the minimum possible size of the largest subgroup!

## 说明/提示

Explanation of the answers for the example $ 1 $ :

1. The first subgroup contains $ 3 $ Assembler fans and $ 2 $ Basic fans, the second subgroup — $ 5 $ C++ fans, the third subgroup — $ 2 $ C++ fans and $ 3 $ Basic fans.
2. The first subgroup contains $ 4 $ Assembler fans, the second subgroup — $ 6 $ Basic fans, the third subgroup — $ 2 $ Basic fans and $ 4 $ C++ fans.
3. The first subgroup contains all Assembler fans, the second subgroup — all Basic fans, the third subgroup — all C++ fans.
4. The first subgroup contains all Assembler fans, the second subgroup — all Basic fans, the third subgroup — all C++ fans.
5. The first subgroup contains $ 12 $ Assembler fans and $ 2 $ Basic fans, the second subgroup — $ 1 $ Assembler fan and $ 13 $ Basic fans, the third subgroup — $ 7 $ Basic fans and $ 7 $ C++ fans.

## 样例 #1

### 输入

```
5
3 5 7
4 8 4
13 10 13
1000 1000 1000
13 22 7
```

### 输出

```
5
6
13
1000
14
```

## 样例 #2

### 输入

```
5
1 3 4
1000 1000 1
4 1 2
325 226 999
939 861 505
```

### 输出

```
3
667
3
517
769
```

# 题解

## 作者：_Violet_Evergarden (赞：8)

这道题是本蒟蒻的第一百道黄题，发一发题解纪念一下。
# 思路
本蒟蒻是在没有仔细看数据范围的情况下写的题目，所以在此提供一种 $O(t)$ 的思路，
也就是分类讨论。

有以下几种情况：

当 $a\leq b \leq c$ 和 $c \leq b \leq a$ 时，我们就很容易想到将中间的 $b$ 分给较小的数然后再进行比较，肯定是三个数都较为平均答案会更优，部分代码如下：
```cpp
if(a>=b&&b>=c){
	if((a+1)/2>=(b+c)){
		cout<<(a+1)/2<<endl;
	}
	else{
		cout<<(a+b+c+2)/3<<endl;
	}
	continue;
}
if(a<=b&&b<=c){
	if((c+1)/2>=(b+a)){
		cout<<(c+1)/2<<endl;
	}
	else{
		cout<<(a+b+c+2)/3<<endl;
	}
	continue;
}
```

当 $a \leq b$ 且 $c \leq b$ 时，我们直接把 $b$ 直接分到两边就行了，部分代码如下：
```cpp
if(a<=b&&b>=c){
	cout<<(a+b+c+2)/3<<endl;
	continue;
}
```
当 $b \leq a \leq c$ 和 $b\leq c \leq a$ 时，我们也是像第一种时一样考虑，但注意有可能 $c$ 的值不需要分配，那么这种请况下就是 $c$ 的值作为最终答案，部分代码如下：
```cpp
if(a>=b&&c>=b&&a>=c){
	if((a+1)/2>=b+c){
		cout<<(a+1)/2<<endl;
	}
	else{
		cout<<max((a+b+c+2)/3,c)<<endl;
	}
	continue;
}
if(a>=b&&c>=b&&a<=c){
	if((c+1)/2>=b+a){
			cout<<(c+1)/2<<endl;
	}
	else{
		cout<<max((a+b+c+2)/3,a)<<endl;
	}
	continue;
}
```

最后我们只需要加上输入输出并将代码组装起来就可以拿下这道题目了。

# 最终代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int t;
int a,b,c;
int main()
{
	cin>>t;
	while(t--){
		cin>>a>>b>>c;
		if(a>=b&&b>=c){
			if((a+1)/2>=(b+c)){
				cout<<(a+1)/2<<endl;
			}
			else{
				cout<<(a+b+c+2)/3<<endl;
			}
			continue;
		}
		if(a<=b&&b>=c){
			cout<<(a+b+c+2)/3<<endl;
			continue;
		}
		if(a<=b&&b<=c){
			if((c+1)/2>=(b+a)){
				cout<<(c+1)/2<<endl;
			}
			else{
				cout<<(a+b+c+2)/3<<endl;
			}
			continue;
		}
		if(a>=b&&c>=b&&a>=c){
			if((a+1)/2>=b+c){
				cout<<(a+1)/2<<endl;
			}
			else{
				cout<<max((a+b+c+2)/3,c)<<endl;
			}
			continue;
		}
		if(a>=b&&c>=b&&a<=c){
			if((c+1)/2>=b+a){
					cout<<(c+1)/2<<endl;
			}
			else{
				cout<<max((a+b+c+2)/3,a)<<endl;
			}
			continue;
		}
	}
	return 0;
}
```
看完这篇题解后，望给一个大大的赞。

---

## 作者：postpone (赞：0)

提供一个比较好理解的思路。

由于 A 组和 C 组的人不能放一起，最终要分成三组。无论怎么分配，本质上都是这样一个过程：

把 B 组中的一些人分给 A 组，剩余的分给 C 组。为了让最大人数最小，接下来将两组中较大的除以 $2$，和较小值比较，得到一个答案。

那么怎么知道具体分配的方案呢，直接枚举 B 组的人数就行了。代码如下。

```cpp
void solve() {
    int a, b, c;
    cin >> a >> b >> c;

    int ans = 1e9;
    for (int i = 0; i <= b; i++) {
        int u = a + i;
        int v = c + b - i;

        if (u < v) {
            swap(u, v);
        }
        int t = u / 2 + (u % 2);
        t = max(t, v);
        ans = min(ans, t);
    }
    cout << ans << "\n";
}
```

---

## 作者：LaDeX (赞：0)

## 解法

题意不用多说。

看数据范围，$a,b,c\leq1000$，则总人数 $n$ 最多为 $3000$，直接可以暴力枚举前两组的人数 $i,j$，第三组人数 $k=n-i-j$，然后判断可行性，再取最值即可。$t$ 最多只有 $5$，不会超时，时间复杂度 $O(n^2)$。

因为 $b$ 的人数不管怎么放也不会冲突，所以优先考虑 $a$ 和 $c$。显然的，我们需要尽可能分开放 $a$ 和 $c$，也就是尽量把全部的 $a$ 放进一组中，把全部的 $c$ 放进一组中，如果不够一组就用 $b$ 补齐。

这里枚举前两组人数 $i,j$，第三组人数 $k = n - i - j$，尽量把 $a$ 全放进第一组，人数最多为 $i$，把 $c$ 全放进第二组，人数最多为 $j$。

注意，可能 $i$ 会大于 $a$ 的人数或是 $j$ 大于 $c$ 的人数，这时候要用 $b$ 来补齐，如果 $b\lt i-a$，就是不足以补齐，那么这种放法就不可行。

如果第一组与第二组这样放满之后，$a$ 和 $b$ 都有剩余，则这种放法不可行。

## Code

```cpp
#include<bits/stdc++.h>
#define LL long long
#define ls(x) (x << 1)
#define rs(x) (x << 1 | 1)
#define mkp(x, y) make_pair(x, y)
#define eb(x) emplace_back(x)
// I Love Yukino Forever!
#define Fcin\
	ios :: sync_with_stdio(0);\
	cin.tie(0); cout.tie(0)
using namespace std;
LL A, B, C;

int main(){
	Fcin;
	LL T;
	cin >> T;
	while (T --){
		cin >> A >> B >> C;
		LL n = A + B + C, Ans = 1e18;
		for (LL i = 1; i <= n - 2; i ++){
			for (LL j = 1; j <= n - i - 1; j ++){
				LL k = n - i - j;
				if (i <= 0 || j <= 0 || k <= 0)
					continue;
				LL t1 = A, t2 = B, t3 = C;
				if (t1 >= i)
					t1 -= i;
				else{
					if (t2 >= i - t1)
						t2 -= i - t1, t1 = 0;
					else
						continue;
				}
				if (t3 >= j)
					t3 -= j;
				else{
					if (t2 >= j - t3)
						t2 -= j - t3, t3 = 0;
					else
						continue;
				}
				if (t1 > 0 && t3 > 0)
					continue;
				Ans = min(Ans, max({i, j, k}));
			}
		}
		cout << Ans << "\n";
	}
	return 0;
}
```


---

