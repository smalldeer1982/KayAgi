# Rocket

## 题目描述

This is an interactive problem.

Natasha is going to fly to Mars. Finally, Natasha sat in the rocket. She flies, flies... but gets bored. She wishes to arrive to Mars already! So she decides to find something to occupy herself. She couldn't think of anything better to do than to calculate the distance to the red planet.

Let's define $ x $ as the distance to Mars. Unfortunately, Natasha does not know $ x $ . But it is known that $ 1 \le x \le m $ , where Natasha knows the number $ m $ . Besides, $ x $ and $ m $ are positive integers.

Natasha can ask the rocket questions. Every question is an integer $ y $ ( $ 1 \le y \le m $ ). The correct answer to the question is $ -1 $ , if $ x<y $ , $ 0 $ , if $ x=y $ , and $ 1 $ , if $ x>y $ . But the rocket is broken — it does not always answer correctly. Precisely: let the correct answer to the current question be equal to $ t $ , then, if the rocket answers this question correctly, then it will answer $ t $ , otherwise it will answer $ -t $ .

In addition, the rocket has a sequence $ p $ of length $ n $ . Each element of the sequence is either $ 0 $ or $ 1 $ . The rocket processes this sequence in the cyclic order, that is $ 1 $ -st element, $ 2 $ -nd, $ 3 $ -rd, $ \ldots $ , $ (n-1) $ -th, $ n $ -th, $ 1 $ -st, $ 2 $ -nd, $ 3 $ -rd, $ \ldots $ , $ (n-1) $ -th, $ n $ -th, $ \ldots $ . If the current element is $ 1 $ , the rocket answers correctly, if $ 0 $ — lies. Natasha doesn't know the sequence $ p $ , but she knows its length — $ n $ .

You can ask the rocket no more than $ 60 $ questions.

Help Natasha find the distance to Mars. Assume, that the distance to Mars does not change while Natasha is asking questions.

Your solution will not be accepted, if it does not receive an answer $ 0 $ from the rocket (even if the distance to Mars is uniquely determined by the already received rocket's answers).

## 说明/提示

In the example, hacking would look like this:

5 2 3

1 0

This means that the current distance to Mars is equal to $ 3 $ , Natasha knows that it does not exceed $ 5 $ , and the rocket answers in order: correctly, incorrectly, correctly, incorrectly ...

Really:

on the first query ( $ 1 $ ) the correct answer is $ 1 $ , the rocket answered correctly: $ 1 $ ;

on the second query ( $ 2 $ ) the correct answer is $ 1 $ , the rocket answered incorrectly: $ -1 $ ;

on the third query ( $ 4 $ ) the correct answer is $ -1 $ , the rocket answered correctly: $ -1 $ ;

on the fourth query ( $ 5 $ ) the correct answer is $ -1 $ , the rocket answered incorrectly: $ 1 $ ;

on the fifth query ( $ 3 $ ) the correct and incorrect answer is $ 0 $ .

## 样例 #1

### 输入

```
5 2
1
-1
-1
1
0
```

### 输出

```
1
2
4
5
3
```

# 题解

## 作者：沉石鱼惊旋 (赞：7)

### 题目翻译

有一个数 $x$，你可以询问**至多** $60$ 次，每次会返回 $0,1,-1$ 中的任意一个数。 $1$ 代表询问的数 $>x$，$-1$ 代表询问的数 $<x$，$0$ 代表询问的数 $=x$。

有时候可能会返回错误的信息，可能会 $1$ 和 $-1$ 交换。但相等时，是不会返回错误信息的。信息返回的周期长度为 $n$。

本题注意事项：

- 得到 $0$ 或 $-1$ 返回时，立即终止程序。

- 本题是交互题，输出后需要 `fflush(stdout);`（C++ 之外的语言请自行查看原题面）。

### 题目思路

至多 $60$ 次，范围在 $1\leq x\leq 1\times 10^9$ 内，明显是二分。

已知一个三十二位有符号整数（C++ 的 `int`）上限为 $2^{31}-1=2,147,483,647$，所以二分算法最坏情况大约要 $30$ 次查询。

但这还不够，我们要知道，每次返回是正确的还是错误的。正好 $n\leq 30$，加上二分次数正好 $60$。
 
我们查询 $n$ 次，每次询问 $1$。$1$ 只可能返回 $1$ 或 $0$，那么 $-1$ 即为错误的。

知道了每次信息是否正确，就能进行二分了。

### 完整代码

```cpp
#include <bits/stdc++.h>
using namespace std;
bool f[50];
int main()
{
    int n, m, cnt = 0;
    cin >> m >> n;
    for (int i = 0; i < n; i++)
    {
        cout << 1 << endl;
        fflush(stdout);
        int x;
        cin >> x;
        if (x == -1)
            f[i] = 0;
        else if (x == 1)
            f[i] = 1;
        else
            return 0;
    }
    int mid, x, l = 2, r = m;
    while (l <= r)
    {
        cnt %= n;

        mid = (l + r) / 2;
        cout << mid << endl;
        fflush(stdout);
        cin >> x;
        if (f[cnt] == 0 && x == -1 || f[cnt] == 1 && x == 1)
            l = mid + 1;
        else if (f[cnt] == 0 && x == 1 || f[cnt] == 1 && x == -1)
            r = mid - 1;
        else if (x == -2 || x == 0)
            return 0;
        cnt++;
    }
    return 0;
}
```

---

## 作者：小闸蟹 (赞：5)

```cpp
// 先求出整个p序列，再二分
#include <iostream>
#include <array>

int Ask(int p)
{
    std::cout << p << std::endl;
    std::fflush(stdout);

    int t;
    std::cin >> t;
    return t;
}     

int main()
{
    constexpr int MaxN = 30 + 5;
    std::array<bool, MaxN> p{ false };

    int m, n;
    std::cin >> m >> n;
    for (int i = 1; i <= n; ++i)    // 先询问n遍1，把p序列求出来，
    {                               // 因为1是最短的距离，所以不可能有-1出现，如果出现了-1，则证明这次是假的答案
        std::cout << 1 << std::endl;
        std::fflush(stdout);
        
        int t;
        std::cin >> t;
        if (t == -1)    // 出现了-1，则证明是假的答案
        {
            p[i] = false;
        }
        else if (t == 1)    // 返回1才对
        {
            p[i] = true;
        }
        else // 恰好1就是答案
        {
            return 0;
        }
    }

    int l = 2, r = m, Now = 1;
    while (l <= r)
    {
        auto m = (l + r) / 2;
        auto Ans = Ask(m);
        if (p[(Now - 1) % n + 1] == false)  // 如果这次火箭会返回假的答案，我们就给它取个反
        {
            Ans = -Ans;
        }
        if (Ans == 0)
        {
            return 0;
        }
        else if (Ans < 0)
        {
            r = m - 1;
        }
        else
        {
            l = m + 1;
        }

        ++Now;
    }

    return 0;
}
```

---

## 作者：野生林登万 (赞：0)

## 简要题意
给你一个二分猜数字的模板交互题，但是交互器会 $n$ 周期性地给出错误的答案，你需要在 $60$ 次内猜出范围为 $[1,10^9]$ 的数

## 思路
说实话应该是大水题，感觉算是水绿  

首先模板二分咱们都会，但是它的交互器会抽风......观察到 $\log_2 10^9$ 差不多刚好是 $60$ 的二倍，提示我们要两次询问解决这个问题。  

首先想到先总的求一次答案再用第二次询问更正答案，不过貌似不太可行，在不知道“抽风序列”的情况下答案都是无效的，甚至可能是非法的（二分不出来，因为部分正确部分错误），所以我们必须求出“抽风序列”  

那么我们先询问 $n$ 次 $1$，显然应该返回 $1$（如果返回 $0$，那么输出答案），否则就是抽风了，记录下来。  

## 小寄巧

这个思路太简单了以至于本题解完泉没有技术含量，就补充一点交互题的小技巧吧。  

输入题一般会让你以“某种方式”和交互库交互，你在不同的情况下会询问不同的内容，但是格式是一样的，你可以把它封装成一个函数，如下：

```cpp
inline int Get(int x){
	cout<<x<<endl;//endl起了flush的效果
	int ret = 0;
	cin>>ret;
	if(ret == 0)exit(0);//防止出现不可预测的情况
	if(ret == -2)exit(0);//题目强调过，这之后流已关闭
	return ret;
}
```

它的好处有

1. 简单明了，降低代码复杂度和阅读复杂度
2. 方便修改，不会因为修改漏了某个复制的代码导致出错
3. 以上都是封装本身的好处，对于交互题封装，他的另外一个好处是在本地 stdio 交互极其困难的情况下，如果你需要调试，可以把封装的 `cin` `cout` 换做自己的交互库。调试完了也方便换回来

所以说还是要有好的代码规范啊。

## 代码

```cpp
#include<bits/stdc++.h>
#define Akano 1
#define pure__Elysia 0
#define loves ^
using namespace std;
const int MAXN = 66;
int n,m,cnt;
inline int Get(int x){
	cout<<x<<endl;
	int ret = 0;
	cin>>ret;
	if(ret == 0)exit(0);
	if(ret == -2)exit(0);
	return ret;
}
bool f[MAXN];
int main(){
	cin>>m>>n;
	for(int i = 1;i <= n;i++){
		int res = Get(1);
		if(res == -1){
			f[i] = true;
		}else{
			f[i] = false;
		}
	}
	int l = 1,r = m+1;
	while(l < r){
		const int mid = (l + r) >> 1;
		int res = Get(mid);
		cnt++;
		if(cnt > n)cnt = 1;
		if(f[cnt])res = -res;
		if(res == -1){
			r = mid;
		}else{
			l = mid + 1;
		}
	}
	return not(Akano loves pure__Elysia);
}
```

~~励志打完所有交互题~~

---

## 作者：oimaster (赞：0)

[不出你的意料，今天我又来写题解了（你可能会问我为什么还没有开学）。这一次我写的题解是一道交互题的题解，毕竟是第一次写这种交互题的题解，写得不太好请大家别太在意，您可以在评论区来留言，我会根据你的留言来完善一下本篇题解或是下一篇题解。](https://oi-master.github.io/post/codeforces-contest-1010-b-and-1011-d-ti-jie/)

好的，我们仍然按照老配方，题面先。

## 题面
### 英文题面
如果你以前看过我写 Codeforces 的题解，你应该很清楚， [这里](https://codeforces.com/contest/1010/problem/B)会挂个链接，而不会写题面。
### 中文题面
请去 [洛谷站内](https://www.luogu.com.cn/problem/CF1010B) 了解。嘿，有点过分，上次是直接复制洛谷的翻译，这次只给个链接？！是的，没错，翻译的很好，“抽风”这个词十分得恰当。
## 思路
省掉了题面，这一篇文章短多了。我们首先假设，火箭不会抽风，那么你会怎么做？很显然，我们可以二分一下这个值，每次输出 $mid$ ，看一下交互器的相应。

但是，事实上没有这么好，火箭随时可能抽风，那么假设我们知道抽风的序列 $p$ ，那么是不是这一道题也很简单？我们看见本轮火箭要抽风了，我们就把火箭的答案反转一下，也可以二分。

问题是，现在我们并不知道 $p$ ，那么怎么搞？等等，我们先放着。

我们可以先了解一下，二分至 $10^9$ 要多少次。我们用 Python 求一下吧。

```python
tmp=1
tot=0
while tmp<1000000000 :
    tot+=1
    tmp*=2
print(tot)

```

输出了 $30$，这时候我们貌似想到了什么……
我们惊讶地发现，火箭抽风的周期也是 $30$ ，加起来就是 $60$ 次！

那么很显然，我们可以拿前 $30$ 次来确定火箭抽风的序列，然后把后 $30$ 次用来二分。这个想法实在是太好了！

还有，我们前 $30$ 次怎么确定？其实我们只需要一直输出 $1$ 就可以了，如果它输出 $1$ ，那么本轮就不会抽风，如果是 $-1$ ，那么就说明会抽风，如果是 $0$ ，那么数据太巧，要特判。

然后，就是可爱的代码啦。
## 代码
```cpp
/* Generated by powerful Codeforces Tool
 * You can download the binary file in here https://github.com/xalanq/cf-tool
 * Author: OI_Master
 * Time: 2020-04-07 07:13:12
**/
#include<bits/stdc++.h>
using namespace std;
#define int long long
signed main() {
	ios::sync_with_stdio(false);
	cin.tie(0);
	int n,m;
	cin>>n>>m;
	int a[m+1],tmp;
	for(int i=1;i<=m;++i){
		cout<<1<<endl;
		cout.flush();
		cin>>tmp;
		if(tmp==0)
			return 0;
		if(tmp==-2)
			return 0;
		if(tmp==1)
			a[i]=1;
		else
			a[i]=0;
	}
	int left=2;
	int right=n;
	int mid;
	int mod=0;
	while(left<=right){
		++mod;
		if(mod==m+1)
			mod=1;
		mid=(left+right)/2;
		cout<<mid<<endl;
		cout.flush();
		cin>>tmp;
		if(tmp==0)
			return 0;
		if(tmp==-2)
			return 0;
		if(a[mod]==0)
			tmp=-tmp;
		if(tmp==1)
			left=mid+1;
		else
			right=mid-1;
	return 0;
}
```

---

