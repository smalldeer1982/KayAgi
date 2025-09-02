# Change a Password

## 题目描述

JAG 办公室的密码是一个由 $N$ 位数字组成的，会定期更改。密码修改规则如下。

1. 新密码的位数与旧密码的位数一样，均为 $N$ 位。同时，新密码的每一个数字最多出现 $1$ 次（旧密码可能存在重复的数字）。
2. 在上述约束下，使得新密码与旧密码的差异最大化（密码之间的差异的定义如下所述）。
3. 如果有两个或两个以上的新密码符合条件，选择最小的密码。

两个密码 $a,b$ 之间的差异是至指 $\min(\vert a-b\vert ,10^{N}-\vert a-b\vert )$，其中 $N$ 为密码的位数。例如，$11$ 和 $42$ 的差异为 $31$，$987$ 和 $012$ 的差异为 $25$。

# 题解

## 作者：sjr3065335594 (赞：0)

~~蒟蒻的第一篇题解~~

首先思考最朴素的暴力，即从 $1$ 开始枚举到 $10^N-1$，肯定会超时。

所以尝试用回溯来枚举每个可能性，这样可以去掉大部分无用情况，在规定时间内枚举完。

这是一道基础的回溯题，那什么是回溯呢？回溯就是当探索到某一步时，发现原先选择并不优或达不到目标，就退回一步重新选择，使用递归来实现。

考虑如果一个数字没有被标记过，就给这个数字打上标记，并去搜索已经填好的部分乘十再加上这一个数字，最后把状态还原。

再来看下细节问题，如何求一个数字的位数呢？我们可以用暴力来拆，也可以通过式子 $\left\lfloor \operatorname{lg} n\right\rfloor+1$ 来直接求，如果你不知道什么是对数，[戳这里](https://baike.baidu.com/item/%E5%AF%B9%E6%95%B0)。

还有前导零的问题，输入数字时，先用字符串存储，求出它的长度后再转换为数字，具体见代码。

```cpp
#include <bits/stdc++.h>//万能头
using namespace std;//命名空间
typedef long long ll;//减少打字时间
string s;
ll a, ans, maxn=-1, len;//记得开long long
bool b[15];//用来标记每个数字是否已经被使用
ll pow10(int x) {//求10^x
    ll sum = 1;//注意初值是1
    for(int i = 1;i <= x;i++)
        sum *= 10;
    return sum;
}
int lg(ll i) {//求一个数的位数
    return (int)(log10(i) + 1);
}
void find(ll n, int dep) {//n表示当前数字是多少，dep表示当前已经枚举多少位数字
    if(dep >= len) {//如果枚举的数字满足了条件
        if(min(abs(n-a), pow10(len) - abs(n-a)) > maxn)
            maxn = min(abs(n-a), pow10(len) - abs(n-a)), ans = n;//更新答案
        return;
    }
    for(int i = 0;i <= 9;i++) {//从0到9枚举每个数字，注意不要忘记0，而且第一位也可以是0
        if(!b[i]) {//如果这个数字没有被用过
            b[i] = 1;//标记一下，防止之后重复使用数字
            find(n * 10 + i, dep + 1);//递归调用下一步，n变成n*10再加上这个数字，dep+1
            b[i] = 0;//回溯，把状态还原
        }
    }
}
int main() {
    cin >> s;//先输入字符串
    len = s.size();//保存字符串长度
    for(int i = 0;i < len;i++)
        a = a * 10 + s[i] - '0';//把数字存到a当中
    find(0, 0);//回溯
    for(int i = 1;i <= len - lg(ans);i++)//处理前导0，如果答案的位数比len小，就要补上0
        cout << 0;
    cout << ans << endl;//输出答案
	return 0;//圆满结束qwq
}
```


---

## 作者：Nygglatho (赞：0)

考虑使用回溯暴力枚举。

由于需要找旧密码的位数 $N$，所以可以先使用`string`，接着再转换成`long long`并且算出 $N$ 以及 $10^N$。
```cpp
for (int i = 0; i < st.size(); ++i) x = x * 10ll + st[i] - 48, pw *= 10;
sz = st.size();//sz 即为位数
```
然后可以开始写回溯，先定义一个数组 $q$，判断这个数字有没有出现过，再把当前的新密码 $p$ 填好后的情况判断出来，即如果填好，那么就比较 $\min(\operatorname{abs}(a - b), 10 ^ N - \operatorname{abs}(a - b))$ 是否大于原来和旧密码的差异最大的新密码，如果当前填出来的新密码大于旧密码，则更新。

反之，如果没有填好，那么可以使用`for`循环，从 $0$ 至 $9$ 枚举，如果 $q_i$ 为假，即没有出现过，那么把 $q_i$ 改为真，并且把当前没填好的这个新密码 $p$ 修改为 $p \times 10 + i$，并重新调用这个函数，调用好了再把 $q_i$ 再次变为假。

这一部分代码：
```cpp
void DFS(int t, long long p) {
	//t为当前新密码位数，用来判断当前新密码是否为真，p为当前新密码
	if (t == sz) {
		if (min(pw - abs(x - p), abs(x - p)) > maxx) {
			y = p;
			maxx = min(pw - abs(x - p), abs(x - p));//更新
		}
	} else {
		for (int i = 0; i <= 9; ++i) {
			if (!q[i]) {
				q[i] = true;//q[i]变成真
				DFS(t + 1, p * 10 + i);//调用自己
				q[i] = false;//q[i]变为假
			}
		}
	}
}
```

---

