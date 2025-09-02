# [POI 2019/2020 R1] Pomniejszenie / 削减

## 题目背景

Bajtek 和 Bitek 是兄弟俩（Bajtek 是哥哥），他们要玩一个游戏。

## 题目描述

游戏规则为：写下较大数的人获胜。

假设 Bajtek 写的是 $A$，Bitek 写的是 $B$。$A$ 和 $B$ 的长度相等，且可能有前导零。

但是每次比赛都是 Bajtek 赢（即总是 $A \ge B$），所以 Bajtek 想输一次。

他现在可以修改 $A$ 上的 **恰好** $k$ 位，使得 $A$ 比 $B$ 小。

求 $A$ 修改后比 $B$ 小的最大值。

如果无法使得 $A$ 比 $B$ 小，输出 `-1`。

因为兄弟俩很喜欢玩这个游戏，所以他们要玩 $t$ 局，即要进行 $t$ 次修改与判断。

## 说明/提示

#### 样例说明

前两组附加样例分别对应附加文件中的 sample1/2.in 和 sample1/2.out。

第三组附加样例为 sample3.zip。

#### 数据规模与约定

**本题采用捆绑测试。**

假设这里的 $n$ 为 $A,B$ 的长度：

- Subtask 1（18 pts）：$1 \le n \le 5$。
- Subtask 2（20 pts）：$1 \le n \le 5000$。
- Subtask 3（20 pts）：$1 \le n \le 10^5$，$k=1$。
- Subtask 4（42 pts）：无特殊限制。

对于 $100\%$ 的数据，$1 \le t \le 100$，$1 \le k \le n \le 10^5$，$A \ge B$。

#### 说明

翻译自 [POI 2019](https://sio2.mimuw.edu.pl/c/oi27-1/dashboard/) C [Pomniejszenie](https://sio2.mimuw.edu.pl/c/oi27-1/p/pom/)。

## 样例 #1

### 输入

```
4
555 333 1
0555 0551 3
0555 0333 4
9 9 1```

### 输出

```
255
0499
-1
8```

# 题解

## 作者：Alex_Wei (赞：13)

> [*P6661 [POI 2019] Pomniejszenie*](https://www.luogu.com.cn/problem/P6661)
>
> [POI 合集](https://www.cnblogs.com/alex-wei/p/POI.html)。

阴间模拟题。考虑求出使得 $A, B$ 不同的第一个位置 $p$，有如下限制：

- 需要修改的位置数量不能超过 $k$。
- 没有考虑到的位置数量不能小于还需要修改的位数。

具体地，对于每一位 $i$，求出 $s$ 表示在第 $i$ 位之前有多少 $A\neq B$ 的位置。$i$ 合法的必要条件是 $B_i \neq 0$，先判掉。由于上述限制要求修改位置数量既不能太小，也不能太大，所以需要考虑当前位是否修改：

- 若 $A_i < B_i$，说明可以不修改。此时若 $s \leq k$ 且 $n - i \geq k - s$ 则 $i$ 合法。
- 若 $B_i > 1$ 或 $A_i > 0$，说明可以 **强制** 修改（因为当 $A_i = 0, B_i = 1$ 时不能修改）。此时若 $s + 1\leq k$ 且 $n - i \geq k - s - 1$ 则合法。

若找不到合法的 $p$ 则无解。输出答案的过程时刻维护 $k$ 表示还需要修改的位数：

- 若当前位 $i$ 小于 $p$，输出 $B_i$。
- 若当前位 $i$ 等于 $p$，此时当 $n - i + 1 = k$ 且 $A_i + 1 = B_i$ 时输出 $B_i - 2$，否则输出 $B_i - 1$，前者因为这一位必须修改（否则将导致剩余位数小于要修改位数，不合法）。
- 若当前位 $i$ 大于 $p$，此时当 $n - i + 1 = k$ 且 $A_i = 9$ 时输出 $8$，否则输出 $9$。
- 注意点：若输出的数码与 $A_i$ 不同，则令 $k$ 自减 $1$。
- 注意点：任何时刻若 $k = 0$，则输出 $A_i$。

时间复杂度线性。

```cpp
#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;

int n, k, p;
char s[N], t[N];
void solve() {
	scanf("%s %s %d", s + 1, t + 1, &k), n = strlen(s + 1), p = 0;
	for(int i = 1, pr = 0; i <= n; i++) {
		if(t[i] - '0') {
			if(s[i] < t[i] && pr <= k && n - i >= k - pr) p = i;
			if((t[i] > '1' || s[i] > '0') && pr + 1 <= k && n - i >= k - pr - 1) p = i;
		} pr += s[i] != t[i];
	} if(!p) return puts("-1"), void();
	for(int i = 1, out; i <= n; i++) {
		if(i < p) out = t[i];
		else if(!k) out = s[i];
		else if(i == p) out = t[i] - 1 - (s[i] + 1 == t[i] && n - i + 1 == k);
		else out = '9' - (n - i + 1 == k && s[i] == '9');
		putchar(out), k -= out != s[i];
	} cout << endl;
}
int main() {
	int T; cin >> T; while(T--) solve();
	return 0;
}
```

---

## 作者：Forever丶CIL (赞：8)


题目大意：给两个数$A，B$。 要求在$A$里面恰好选$k$位，改变它们的值，让$A$小于$B$ 且$A$最大。

先复习一下，两个$n$位的数$A,B$，如何比较它们的大小？

很简单，如果$A,B$的前$i-1$位都一模一样，但是$A$的第$i$位大于$B$的第$i$位那么后边不用看了，$A$必然大于$B$ 。

好了回来继续看这个题，那么我们要让$A$小于$B$，就要选择一个目标位$Tar$，使得$A$的前$Tar$位都和$B$的前$Tar$位相同，而$A$的$Tar$位恰好等于$B$的$Tar$位$-1$。

现在$A$小于$B$在思想上已经搞定了，我们需要考虑还要让$A$最大的事情了，这个事情也很简单，剩下所有位都是$9$的话不就可以了么。

以上两段就是本题最关键的贪心思想，现在我们来开始做这个题。

首先是找这个$Tar$。 $Tar$怎么找？可以一位一位枚举，看看这一位可以不可做这个$Tar$，而且为了让$A$尽可能大，这个$Tar$我们要让它尽量靠后。（例子：$A$:234 ; $B$:547 例子里我们先不考虑k啊; 因为第$Tar$位是决定$A$和$B$大小的一位，如果$Tar=1$，那么按照我们的贪心，$A=499$, 而$Tar=2$时，$A=539$, 当$Tar=3$时，$A=546$，很容易看出来$Tar$越大，得到的$A$越大）

但是因为有k的限制，我们的$Tar$也不能太大了，至少说当我们想要取第$i$位做$Tar$时，得保证前$i$位$A,B$不同的位数+$i$后面还剩下的位数得大于等于$k$。

现在我们有疑问了，首先是我前面一直在说“前$i$位$A,B$的不同的位数”，但是我们还没算第$Tar$位呢，第$Tar$位如果说$A$大于$B$，那么我们的操作是让$A_{Tar}=B_{Tar}-1$吧？其实不一定，如果$B_{Tar}=0$怎么办？  其次是我前面说 “剩下所有位都是$9$的话不就可以了么。” ，很显然啊，如果原来$A$的后面几位中就有 $'9'$怎么办啊。

现在我们一个个解决疑问，首先如果$B_{i}=0$ 那么这一位不可能成为$Tar$，我们在枚举的时候要跳过去，(要是还需要问这个的原因的话：因为如果$A,B$前$Tar$位相同，而$B_{Tar}=0$那么不管$A_{Tar}$等于几，都不能让$A < B$，和我们最开始给$Tar$的定义就矛盾了)

其次如果$A$的后几位中本来就有$'9'$那么当我们把$A$的$Tar$位后面的不是$9$的位都变成$9$之后，如果这个时候变换次数仍然不够$k$次，我们应该从后往前把$A$中原来就是$9$的位变成$8$（如果还需要问为什么这样最优：因为在前$Tar$位都确定了，并且$Tar$后面的位都是$9$的前提下，假如，我们还需要变$x$个数，然后呢，$A$数组的$Tar$位之后有$y$个本来就是$9$的位, $x\le y$ ,那么，为了把这$x$个操作做完，我们必须得拿这些原来就是$9$的位开刀了，而且一过脑子就能想出来，肯定是从后往前把那些本来就是$9$的位变成$8$）


我感觉我写的非常啰嗦，主要是为了能让更多的人看明白。（~~其实是我语文太差了~~）

上面一堆废话只为了介绍思想，现在我们把所有东西串起来，说一下写法。

首先读入数据，用$len$表示数的长度，然后从$1$到$len$枚举每一位，当枚举到第$i$位时，如果$B_{i}=0$直接跳过，否则来判断这个$i$能不能当$Tar$，最后枚举完了，我们也找到了最优的$Tar$。现在我们要开始构造答案了，第一步是$Tar$以前的每一位$A_{i}=B_{i}$，第二步是决定第$Tar$位怎么变，如果$A_{Tar}\ge B_{Tar}$ 或者$A_{Tar}< B_{Tar}-1$，那么$A_{Tar}= B_{Tar}-1$ ； 如果$A_{Tar}=B_{Tar}-1$ 那就先不动它了。 第三步是把$Tar$以后的不等于$9$的位都变成$9$，第四步是把原来就是$9$的从后往前变成$8$，第五步是，如果在第三步中 “那就先不动它了” 这样的情况发生的话，有可能这个时候我们的变换次数离$k$还差$1$，这个时候我们最优的操作就是 "动它" 把$A_{Tar}$减去$1$;（注意：以上五步，第一步是必走的，在$A_{Tar}\ge B_{Tar}$的情况下 ，第二步必走，其他几步，都是要看我们当前的操作数，有没有到$k$，不到的话，再操作。）

到这里可能还有一个疑问，就是为啥这样子，到最后能保证恰好换$k$次？ 因为如果换不到$k$次，我们会第二步，第三步，一直进行下去。 那为啥不会出现第五步走完还不够$k$次？ 前面写了$->$“我们的$Tar$也不能太大了，至少说当我们想要取第$i$位做$Tar$时，得保证前$i$位$A,B$不同的位数+$i$后面还剩下的位数得大于等于$k$。”不过这句话不够严谨，应该分三部分，前$i-1$位中不同的位数（$cnt1$），$i$位之后剩余的位数($cnt2$)，第i位（$1$）, $cnt1+cnt2+1\ge k$ 这样子，如果$cnt1+cnt2+1>k$ 即$cnt1+cnt2\ge k$ 那么就算第二步得到时候我们 "那就先不动它了" 也最多进行到第四步结束。如果$cnt1+cnt2+1=k$ 那么如果第二步我们 "那就先不动它了" 就会出现，当把第四步做完时，$cnt1,cnt2$都做了，还差$1$，就要做第五步了。

参考代码： 仅供参考，因为菜菜的我改了好几遍才过，所以代码中赘余的成分比较多，比如一个if就行的整了好几个if，一个变量就够的用了好几个变量23333. 

而且大概是我自带大常数，O(n)的算法，我写出来就是900ms险过，我同学就是400ms稳过，qwq哭了///

------------

```cpp
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int Maxn=100010;
int t,k;
char A[Maxn],B[Maxn];
int a[Maxn],b[Maxn]; //用a,b分别存A,B
void Solve()
{
    scanf("%d",&t);
    while(t--)
    {
        scanf("%s%s%d",A+1,B+1,&k);
        int len=strlen(A+1);
        for(int i=1;i<=len;i++) a[i]=A[i]-'0',b[i]=B[i]-'0';
        int cnt=0,Tar=-1;
        //cnt是用来记录前i位不同的位数，而nowc呢，我这里写的比较冗长，其实并没啥用。
        for(int i=1;i<=len;i++)
        {
            if(b[i])
            {
                int nowc=0;
                if(a[i]>=b[i])
                {
                    nowc=cnt+1;
                    if(nowc<=k&&nowc+len-i>=k) Tar=i;
                }
                else 
                {
                    if(b[i]>1)
                    {
                        nowc=cnt;
                        if(nowc<=k&&nowc+len-i+1>=k) Tar=i;
                    }
                    else
                    {
                        nowc=cnt;
                        if(nowc<=k&&nowc+len-i>=k) Tar=i;
                    }
                    
                }
            }
            if(a[i]!=b[i]) cnt++;
        }

        if(Tar==-1){printf("-1\n"); continue ;}
        
        cnt=0;
        for(int i=1;i<=Tar-1;i++) if(a[i]!=b[i]) cnt++,a[i]=b[i];
        
        if(a[Tar]>=b[Tar]) cnt++,a[Tar]=b[Tar]-1;
        else if(cnt<k&&a[Tar]!=b[Tar]-1) cnt++,a[Tar]=b[Tar]-1;
        
        if(cnt<k)
        {
            for(int i=Tar+1;i<=len;i++) if(A[i]!='9'&&cnt<k) cnt++,a[i]=9;
        }
        if(cnt<k)
        {
            for(int i=len;i>=Tar+1;i--) if(A[i]=='9'&&cnt<k) cnt++,a[i]=8;
        }
        
        if(cnt==k-1) cnt++,a[Tar]--;
        for(int i=1;i<=len;i++) printf("%d",a[i]); puts("");
    }
}
int main()
{
    Solve();
    return 0;
}

```

---

## 作者：CommonDigger (赞：6)

![](https://picx.zhimg.com/70/v2-f6957a0cbc79146e376c1fb738245ea3_1440w.awebp?source=172ae18b&biz_tag=Post)
~~蒟蒻写的，轻点喷，求求了~~

[博客](https://www.luogu.com.cn/blog/551417/)内食用[本文章](https://www.luogu.com.cn/blog/551417/page6661on24feb14)更佳qwq。**真的更佳！不骗你！**
## 题意
此题的题意很明确，没有任何隐藏的信息。一共有 $t$ 组数据，对于每一组数据，给出两个**位数相同**的数（可能带前导零）$A$ 和 $B$，修改 $k$ 步将 $A$ 变成小于 $B$ 的尽可能大的值。

下文的分析过程如果没有看懂，欢迎你在评论区问我或者私信。
## 分析
很明显，这道题有多重数据，而且每一个数据肯定不会是超级小的那种，所以我们要的是一种一次或两次循环搞定的办法。

先看几个例子，了解一下修改过程是如何工作的。
> $k=4$  
> $000457126715-A$  
> $000450613252-B$

A 应修改为：
> $00045\underline{0612}715-A$  
> $000450613252-B$

这个例子中，$A$ 一共修改了 $4$ 位，前三位修改之后**与其对应的 $B$ 的该位相同**了；修改的第四位这里的 $A_i$ 比 $A_i$ **正好小 $1$**。

这里，我定义几个变量。

假设一个唯一数 $q$，有 $a_1=b_1,a_2=b_2\cdots a_{h-1}=b_{h-1}$，而 $a_q\neq b_q$。也就是说，**第 $q$ 位是 $a$ 和 $b$ 出现第一个不一样的地方。**~~（表达能力太差）~~

定义一个变量 $p$，我称之为*界点*。如果还需要进行 $k$ 次修改，则界点就是字符串的倒数第 $k$ 位，相当于一个底线。显然，如果进行了一次修改，那么剩余修改次数就要减一，界点随之后移一位。

整道题大概的思路就是前期尽量保持 $a_i=b_i$，有需要的话就找到唯一位置 $q$，为了让 $A$ 比 $A$ 小，就要**令** $a_q=b_q-1$。然后，因为 $A$ 前面的高位已经比 $B$ 小了，就可以尽量把后面的数改大（因为题目要求修改之后的 $A$ 尽量大）。

### 完整的思路如下：
- 字符数组存储的范围是 $0\sim n-1$，循环变量 $i$ 从下标零开始遍历。
- 两个字符串有时候会存在公共前导零的部分，用一个变量保存公共前导零部分的最后一位的位置。
- 如果界点在公共前导零的部分，则**无法修改**。
- $i$ 遍历完公共前导零之后，继续遍历。如果 $a_i\neq b_i$就在这个位置修改一次使两串这一位相同，并移动界点。完成后**判断**：
- 判断 1：如果界点等于 $n$，意思是修改次数已使用完。这个时候我们不知道后面的部分是否 $A<B$，所以遍历一下进行判断。  
*如果* $A<B$，那么这个时候已经得到答案了，**输出**；  
*如果* $A=B$ 或 $A>B$，则需要将现有的 $A$ 改小。从此处的 $i$ 往前看：如果 $b_i=0$ 或*特殊情况(见下)，就*不能修改，否则在这个位置将 $A_i$ 改为 $B_i-1$。这个位置就是 $q$。以后的位置全部改为 $9$。
- 判断 2：如果 $i$ 到了界点而修改次数还有多余，则无论如何必须开始修改。按照上文的步骤找到 $q$ 进行修改，后面也是全部改成 $9$。
- 改 $9$ 的过程中，如果 $a_i$ 本来就是 $9$，就跳过不改。如果改到结尾 $k$ 次修改还没用完，就从后往前将 $A_i$ 已经是 $9$ 的位置改成 $8$。在这之后次数还没使用完就**无法修改**。

对于上文中的特殊情况，是指在找 $q$ 的过程中，遇到了 $i$ 在界点上，而 $A_i=0,B_i=1$。这种情况是不能修改的，需要忽略掉继续往前找。然后，找 $q$ 的过程中如果遍历到了公共前导零还是找不到，则**无法修改**。最后，如果 $q$ 在界点上而 $A_i$ 本身就等于 $B_i-1$，就令 $A_i=B_i-2$。

思路就这些，下面是代码：
```cpp
#include "iostream"
#include "cstring"
using namespace std;
int t, k, n, p, q, leading;
char a[100005], b[100005], edited[100005]; // edited:修改答案
bool cmp(int i){ // 比较从i开始后面这一部分 a 是否大于 b，大于就返回 false
    for(;i<n;i++){
        if(a[i]<b[i]) return true;
        else if(a[i]>b[i]) return false;
    }
    return false;
}
bool update_q(int i){
    while(1){
        if(i==leading) return false;
        if(a[i]!=b[i]) edited[i]=a[i], p--;
        if(b[i]!='0' && (i!=p || b[i]!='1' || a[i]!='0')) break;
        i--;
    }
    q=i;
    return true;
}
bool edit9(int i){ // 全部改成 9 的函数
    for(;p<n&&i<n;i++){
        edited[i]='9';
        if(a[i]!='9') p++;
    }
    if(p==i){ // 修改次数用完了，就将后面的部分炒上去，然后得出结果
        for(;i<n;i++) edited[i]=a[i];
        return true;
    }
    i=n-1; // 没修改完，就从后往前改 8
    for(;p<n;i--){
        if(i<=q || i<=leading) return false;
        if(a[i]=='9') p++, edited[i]='8';
    }
    return true;
}
bool operate(){
    n=strlen(a), p=n-k; // p：界点
    for(int i=0;i<n;i++) edited[i]=a[i];
    int i=0;
    while(a[i]=='0' && b[i]=='0') i++;
    leading=i-1; // 前导零最后一位
    if(leading>=p) return false; // 界点开始在前导零上，就不能修改
    while(1){
        if(a[i]!=b[i]) edited[i]=b[i], p++;
        if(p==n || i==p){
            if(p==n && cmp(i+1)) return true;
            if(!update_q(i)) return false; // 找 q
            if(a[q]!=b[q]-1) p++, edited[q]=b[q]-1; // 一般改
            else if(q==p) p++, edited[q]=b[q]-2; // 特殊情况即 b[i]-2
            if(!edit9(q+1)) return false;
            return true;
        }
        i++;
    }
}
int main(){
    cin >> t;
    while(t--){
        cin >> a >> b >> k;
        if(!operate()) printf("-1\n");
        else{
            for(int i=0;i<n;i++) printf("%c", edited[i]);
            printf("\n");
        }
    }
}
```

---

## 作者：船酱魔王 (赞：3)

# P6661 [POI 2019] Pomniejszenie 题解

## 题意回顾

给定两个大数（允许存在前导 0）$ A,B $，要求修改 $ A $ 正好 $ k $ 位使得 $ A<B $ 且 $ A $ 最大。输出最大的 $ A $。

多测，$ T $ 组数据，$ T \le 100 $，$ |A|,|B|\le 10^5 $，$ A\ge B $。

## 分析

按照字符串方式表示 $ A,B $，$ A_i $ 表示 $ A $ 的第 $ i $ 位。

我们发现，存在位置 $ r $ 使得 $ \forall 0 \le i < r $，$ A_i = B_i $ 且 $ A_r<B_r $。

显然，我们要使得 $ r $ 最大，$ \forall r \le i < n $，$ A_i $ 最大。

我们从头开始依次枚举 $ r $，我们维护 $ 1 \sim r-1 $ 位置与 $ B $ 的不同位置个数记为 $ df $，则分以下情况讨论：

* $ A_r\ge B_r $ 时，要求 $ df+1 \le k $。

* $ A_r < B_r $ 时，要求 $ df \le k $。

* $ B_r \ne 0 $。

* $ A_r=0,B_r=1 $ 时，这一位一定不能改动，因此要求 $ n-r > k-df $。(因为不能改成本身浪费修改次数）

* 要求 $ n-r \ge k-df $。（$ B_r \ge 2 $ 时，可以改第 $ r $ 个位置）

接下来，根据剩余修改次数、是否必须修改、$ A_r $ 原始值决定 $ r $ 位置我们能填 $ B_r-1 $，$ B_r-2 $，或者原封不动。

对于 $ r + 1 \sim n-1 $ 位置，我们从高位到低位能填 $ 9 $ 就填 $ 9 $，如果次数过多就从低位到高位把原来的 $ 9 $ 改成 $ 8 $。

本题数据强，边界情况测试点（俗称 corner case）较多，注意修改次数要求过高、修改次数很接近 $ r $ 之后的数字个数这两种极端情况。

调不出来可以从 LOJ 上下载小数据。

## AC 代码

```
#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
int T;
int n;
string s, t;
int k;
int main() {
    //freopen("pom1.in", "r", stdin);
    //freopen("pom.out", "w", stdout);
    cin >> T;
    for(int ti = 1; ti <= T; ti++) {
        cin >> s >> t >> k;
        n = s.size();
        int mr = -1;
        int dk = 0;
        int df = 0;
        for(int r = 0; r < n; r++) {
            if(df > k) {//Too many things to change!!!
                if(s[r] != t[r]) {
                    df++;
                }
                break;
            }
            if(df == k && s[r] >= t[r]) {//You need to change this digit but you can't
                if(s[r] != t[r]) {
                    df++;
                }
                continue;
            }
            if(t[r] == '0') {//This digit can't be the divider
                if(s[r] != t[r]) {
                    df++;
                }
                continue;
            }
            if(k - df > n - r) {
                if(s[r] != t[r]) {
                    df++;
                }
                continue;
            }
            if(s[r] == '0' && t[r] == '1' && k - df == n - r) {
                if(s[r] != t[r]) {
                    df++;
                }
                continue;
            }
            mr = r;
            dk = k - df;
            if(s[r] != t[r]) {
                df++;
            }
        }
        if(mr == -1) {
            printf("-1\n");
            continue;
        }
        for(int i = 0; i <= mr; i++) {
            if(i < mr) {
                s[i] = t[i];
            } else if(i == mr) {
                if(n - i == dk && s[i] == t[i] - 1) {
                    s[i] = t[i] - 2;
                    dk--;
                } else {
                    if(dk == 0) {
                        continue;
                    }
                    if(s[i] != t[i] - 1) {
                        dk--;
                    }
                    s[i] = t[i] - 1;
                }
            }
        }
        for(int i = mr + 1; i < n; i++) {
            if(s[i] != '9' && dk > 0) {
                dk--;
                s[i] = 'X';
            }
        }
        for(int i = n - 1; i > mr; i--) {
            if(s[i] == 'X') {
                s[i] = '9';
            } else if(s[i] == '9' && dk > 0) {
                dk--;
                s[i] = '8';
            }
        }
        cout << s << endl;
    }
    return 0;
}

```

---

## 作者：Shunpower (赞：2)

一般地，我们从低位到高位考虑 $i$，尝试钦定 $i-1$
及其前面的位都相等，$a_i<b_i$，然后后面的随便。由贪心可知只要我们能判定可行，那么无论如何构造方案，都比继续枚举下去更优秀。

考虑如何判断可行性。

显然第一个必要条件是 $b_i\neq 0$。

令 $[0,i)$ 中 $a_i\neq b_i$ 的位有 $x$ 个，那么 $[i,n]$ 中必须修改 $r=k-x$ 位，显然存在必要条件 $0\leq r\leq n-i+1$。

我们发现 $i$ 这一位需要贪心。但是 $(i,n]$ 的可以乱取，所以考虑区分 $r=n-i+1$（每一位都需要改变）和 $0<r\leq n-i$（第 $i$ 位可以不动）和 $r=0$。

对于 $r=0$，由于后面的位都不能动，所以：

- 若 $a_i<b_i$，直接按照钦定把前 $i-1$ 位进行 $a_i\gets b_i$ 就是一个构造。
- 若 $a_i=b_i$，可以转化到 $i+1$ 及其之后去处理。
- 若 $a_i>b_i$，非法。

对于 $r=n-i+1$，第 $i$ 位必须要动且必须比 $b_i$ 小，所以：

- 若 $a_i\neq b_i-1$，使 $a_i\gets b_i-1$，$(i,n]$ 的构造转化为 $r\leq n-i$。
- 若 $a_i=b_i-1$：
  - 若 $a_i=0,b_i=1$，非法。
  - 使 $a_i\gets b_i-2$，$(i,n]$ 的构造转化为 $r\leq n-i$。

然后考虑 $r\leq n-i$ 怎么做。显然此时我们可以直接令 $a_i\gets b_i-1$，然后用剩下的步数构造 $(i,n]$。

因为这一部分是可以随便乱动的，所以我们从高位到低位先把所有 $a_i\neq 9$ 变成 $9$。

如果还有剩下的步数，那么从低位到高位把 $a_i=9$ 变成 $8$。

显然由于 $r$ 的范围一定可以得出构造。

```cpp
string a,b;
int k;
int n;
int sum[N];
string sa;
void solve(){
    cin>>a>>b>>k;
    a='@'+a,b='@'+b;
    sa=a;
    n=a.length()-1;
    fr1(i,1,n) sum[i]=sum[i-1]+(a[i]!=b[i]);
    fr2(i,n,1){
        if(b[i]=='0') continue;
        int rem=k-sum[i-1];
        if(rem>=0&&rem<=n-i+1){
            rem-=(a[i]!=b[i]-1);
            if(rem>=0){
                if(rem==n-i+1&&b[i]>='2') a[i]=b[i]-2;
                else if(rem!=n-i+1) a[i]=b[i]-1;
                else continue;
                fr1(j,i+1,n){
                    if(!rem) break;
                    if(a[j]!='9') a[j]='9',rem--;
                }
                fr2(j,n,i+1){
                    if(!rem) break;
                    if(sa[j]=='9') a[j]='8',rem--;
                }
            }
            else if(a[i]>=b[i]) continue;
            fr1(j,1,i-1) a[j]=b[j];
            fr1(j,1,n) cout<<a[j];
            cout<<'\n';
            return;
        }
    }
    cout<<"-1\n";
}
```

---

## 作者：huangrenheluogu (赞：2)

题解中，记数字字符串 $\overline{s_1s_2\cdots s_n}$，第 $i$ 位为 $s_i$。

细节其实可以不是很多，但需要考虑周全。

考虑枚举 $A,B$ 第 $i$ 位第一次，可以预处理 $dif_i$ 表示满足 $1\le j\le i,A_j\ne B_j$ 的 $j$ 的数量。

显然，这个不同的位越往后越好，因此是可以直接贪心的。

考虑从 $B_i-1\sim 0$ 倒序枚举第 $i$ 位的数字，因为这一位数字最大越好，因此倒序枚举之后可以直接输出。

第 $1$ 位到第 $i$ 位需要修改次数为 $dif_{i-1}+[a_i\ne num]$，记为 $tmp$。这次可以修改的条件为 $tmp\le k$ 并且 $tmp+n-i\ge k$，前面是修改必须修改的前 $i$ 位不超，后面是可以修改的 $i+1\sim n$ 位修改之后可以达到 $k$ 次的限制。

如果可行，就进行修改，前面的修改是容易的，后面的部分先正序把不是 $9$ 的变成 $9$，然后倒序把本来是 $9$ 的变成 $8$，达成条件。

```cpp
#include<bits/stdc++.h>
using namespace std;
const int N = 1e5 + 5;
int T, n, k, dif[N], tmp;
char a[N], b[N];
bool vis[N];
inline void clr(){
    for(int i = 1; i <= n; i++){
        a[i] = b[i] = '\0';
        vis[i] = 0;
    }
}
inline void solve(){
    for(int i = n; i; i--){
        if(b[i] == '0') continue ;
        for(char num = b[i] - 1; num >= '0'; num--){
            tmp = dif[i - 1];
            if(a[i] != num) tmp++;
            if(tmp <= k && tmp + n - i >= k){
                for(int j = 1; j < i; j++){
                    if(a[j] != b[j]) a[j] = b[j], k--;
                }
                if(a[i] != num) a[i] = num, k--;
                for(int j = i + 1; j <= n && k; j++){
                    if(a[j] != '9'){
                        a[j] = '9';
                        vis[j] = 1;
                        k--;
                    }
                }
                for(int j = n; j >= i + 1 && k; j--){
                    if(!vis[j]){
                        a[j] = '8';
                        k--;
                    }
                }
                printf("%s\n", a + 1);
                return ;
            }
            
        }
    }
    puts("-1");
}
int main(){
    // freopen("modify.in", "r", stdin);
    // freopen("modify.out", "w", stdout);
    scanf("%d", &T);
    while(T--){
        scanf("%s%s%d", a + 1, b + 1, &k);
        n = strlen(a + 1);
        for(int i = 1; i <= n; i++){
            dif[i] = dif[i - 1] + (a[i] != b[i] ? 1 : 0);
        }
        solve();
        clr();
    }
    return 0;
}
```

---

## 作者：Nuyoah_awa (赞：2)

### 题目大意

给你两个数 $A, B$，修改 $k$ 次 $A$，使得 $A < B$，求满足条件的最大的 $A$。

### 题目分析

要使 $A < B$ 且 $A$ 尽可能大，我们需要使 $A$ 尽可能的接近 $B$。

我们先考虑如不考虑修改次数的情况下，答案一定是像下面一样：

$$A:A_1, A_2, \dots A_{t-1}, A_t, A_{t+1}, \dots, A_n$$
$$B:B_1, B_2, \dots B_{t-1}, B_t, B_{t+1}, \dots, B_n$$
$$C:B_1, B_2, \dots B_{t-1}, B_t - 1, 9, \dots, 9$$

也就是前面有一段与 $B$ 一样，然后有一位略小于 $B$，后面一段尽可能的大。

然后考虑修改次数，即前面一段 $A_i\neq B_i$ 的个数，加上 $1$，再加上后面一段 $C_i \neq B_i$ 的个数。

为了使 $A_i$ 尽可能的大，我们需要使前面一段尽可能的长，于是，我们可以枚举中间一位，使其尽量靠右且满足条件。

然后答案就是前面一段为 $B_i$，中间一位根据情况为 $B_i-1$ 或 $B_i-2$，后面根据剩余次数尽可能大。

### code

```cpp
#include <iostream>
#include <cstdio>

using namespace std;

const int N = 1e5 + 5;
int T, n, k, s[N];
string a, b, c;
bool flag;

int main()
{
    scanf("%d", &T);
    while(T--)
    {
        cin >> a >> b;
        n = a.size();
        a = "#" + a, b = "#" + b;
        c = a;
        scanf("%d", &k);
        for(register int i = 1;i <= n;i++)
            s[i] = s[i-1] + (a[i] != b[i]);
        register int tmp = 0;
        for(int i = 1;i <= n;i++)
        {
            if(b[i] == '0')
                continue;
            if(a[i] < b[i] && s[i-1] <= k && s[i-1] + n - i >= k)
                tmp = i;
            if(s[i-1] + 1 <= k && s[i-1] + 1 + n - i >= k && !(a[i] == '0' && b[i] == '1'))
            	tmp = i;
        }
        if(tmp == 0)
        {
            printf("-1\n");
            continue;
        }
        for(register int i = tmp-1;i >= 1;i--)
            c[i] = b[i];
        k -= s[tmp-1];
        if(!k)
        	c[tmp] = a[tmp];
        else
        	c[tmp] = ((n - tmp + 1 == k && (a[tmp] == b[tmp] - 1)) ? b[tmp] - 2 : b[tmp] - 1);
    	k -= c[tmp] != a[tmp];
        for(int i = tmp + 1;i <= n && k;i++)
        {
        	if(!k)
        		c[i] = a[i];
        	else
        	{
	            c[i] = ((n - i + 1 == k && a[i] == '9') ? '8' : '9');
				k -= (c[i] != a[i]);
			}
		}
        cout << c.substr(1, n) << endl;
    }
    return 0;
}
```

---

## 作者：Hog_Dawa_IOI (赞：0)

细节！！！细节！！！满满的细节！！！校内模拟赛被硬控啊！！！   
需要明确一点的是：我们会找到一个位置，使得修改后从这里开始 $A$ 比 $B$ 小，并且能达成任务；在这个基础上，我们希望能尽可能的把 $A$ 后面的数字修改的尽量大。     
于是我们把算法分成 $2$ 个部分分别去完成。  

-------
### Part 1
找到一个位置，使得修改后从这里开始 $A$ 比 $B$ 小，并且能达成任务，记为 $i$。      
$A$ 的第 $i$ 位记为 $A_i$，$B$ 同理，并记 $i$ 之前两个数字不同位个数为 $diffe$。        
1. $B_i$ 不能是 $0$，否则 $A$ 无法修改到比它还小的值。     
2. 如果 $A_i < B_i$，那么这一位不必修改。此时要满足：
- $diffe \le k$。前面不同的数都能够被修改，此时只需要把 $A$ 的前 $i-1$ 位修改为和 $B$ 相同即可。
- $n-i \ge k-diffe$。剩余的修改次数要能被用完。
3. 如果 $A_i$ 能被强制修改为 $<B_i$ 的值，那么我们的修改次数就要被消耗 $1$。此时我们仍然需要满足和上面一样的条件。     
- 如果 $A_i=0$ 且 $B_i =1$，那么 $A_i$ 不能被强制修改为 $<B_i$ 的值，反之都可以。  
- 强制修改是为让修改次数恰好为 $k$ 提供更大可能。
---------
### Part 2
修改数字并输出。    
当然如果找不到一个 $i$ 满足条件那么输出 $-1$。     
1. 在 $i$ 之前，期望让 $A$ 和 $B$ 相等，输出 $B$ 的当前位（前面已经保证肯定可以做到）。
2. 如果很不幸修改次数已被用完，那么输出 $A$ 的当前位。
3. 如果当前位为 $i$。
- 按照期望，应该把这一位修改为 $B_i-1$。
- 如果 $A_i=B_i-1$，那么相当于没修改。但如果剩余修改次数又强制要求你修改（当前位及以后的位数等于 $k$），那么不好意思，这里必须再修改为 $B_i-2$。因为在第一步中保证了只有选择第三种情况才会出现这样的局面，而当时又判掉了 $A_i=0,B_i=1$ 的情况，所以这里不可能被减成负数。
4. 在 $i$ 之后，我们就要尽量让当前位尽量大（尽量为 $9$）。由于前面判掉了次数被用完的情况，现在次数肯定有剩余。
- 像上面说的，如果当前位本身就是 $9$，剩余修改次数强制要求你修改，那么可以把当前位改为 $8$。这样能尽量保证利益最大化。

二者结合，就可以通过本题。
```cpp
#include<stdio.h>
#include<string.h>
int t,k,n;char s1[100005],s2[100005];
int main()
{
    scanf("%d",&t);
    while(t--)
    {
        scanf("%s%s%d",s1+1,s2+1,&k),n=strlen(s1+1);int whe=0;
        for(int i=1,diffe=0;i<=n;diffe+=(s1[i]!=s2[i]),i++) if(s2[i]!='0')
        {
            if(s1[i]<s2[i]&&diffe<=k&&n-i>=k-diffe) whe=i;
            if((s1[i]>'0'||s2[i]>'1')&&diffe+1<=k&&n-i>=k-diffe-1) whe=i;
        }
        if(!whe) {printf("-1\n");continue;}
        for(int i=1;i<=n;i++)
        {
            char put;if(i<whe) put=s2[i];
            else if(k==0) put=s1[i];
            else if(i==whe) put=s2[i]-1-(s1[i]==s2[i]-1&&n-i+1==k);
            else if(i>whe) put=(s1[i]=='9'&&n-i+1==k)?'8':'9';
            printf("%c",put),k-=(put!=s1[i]);
        }
        printf("\n");
    }
}
```

---

## 作者：xukehg (赞：0)

细节多的爆炸的题目。

在合法的情况中，为了使 $A$ 尽量大，因该让 $A，B$ 相等的前缀尽量长，倒叙枚举前缀相同的最后一位的后一位，不妨设为 breakpoint，则 $a_{breakpoint}$ 在期望中应等于 $b_{breakpoint} - 1$，问题在于如何判断正确性，不妨令 $sum_i$ 记为使前 $i$ 位相等的次数，$chk(i)$ 表示第 $i$ 位是否满足 $a_i + 1 \neq b_i$ 则有如下几种情况：

1. 若 $b_i \ge 1$ 且 $sum_{i - 1} + chk(i) \leq k$ 且 $sum_{i - 1} + chk(i) + n - i \ge k$，即在此处更改既不会多用次数，也不会不够用，则能成为断点。

2. 若 $b_i \ge 1$ 且 $sum_{i - 1} \leq k$ 且 $sum_{i - 1} + n - i \ge k$ 且 $a_i < b_i$，即这一位不进行修改但此位合法，仍可以成为断点。

3. 若 $b_i \ge 2$ 且 $sum_{i - 1} + 1 \leq k$ 且 $sum_{i - 1} + 1 + n - i \ge k$ 且 $a_i < b_i$，即这一位尽管 $chk(i)$ 为否，仍强制变动，则 $a_i$ 被修改为 $b_i - 2$。

4. 如果以上情况均不满足，则不能成为断点。

输出答案则在断点之前强制相等，断点处特判是以上哪种情况，断点后能填 $9$ 就填 $9$，$a_i$ 是 $9$ 就填 $8$，$a_i$ 是 $9$ 就检查后面能否用完次数，能就输出 $9$，否就输出 $8$。

代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 5;

int n,k;
string s,t;
int sum[N];
int dot;
int chk(int i){
	if ((s[i] - '0' + 1) == (t[i] - '0')) return 0;
	else return 1;
}
bool check(int i){
	if (sum[i - 1] + chk(i) <= k && sum[i - 1] + chk(i) + n - i >= k) return true;
	if (sum[i - 1] <= k && sum[i - 1] + n - i >= k && (s[i] - '0' < t[i] - '0')) return true;
	if (sum[i - 1] + 1 <= k && sum[i - 1] + n - i + 1 >= k && t[i] - '0' > 1 && (s[i] - '0' < t[i] - '0')) return true;
	return false;
}
void clear(){
	for(int i = 1;i <= n;i++) sum[i] = 0;
	s = "",t = "";
	n = 0;
}
void solve(){
	cin >> s >> t >> k;
	n = s.size();
	s = " " + s,t = " " + t;
	sum[0] = 0;dot = -1e9;
	for (int i = 1;i <= n;i++){
		sum[i] = sum[i - 1];
		if ((s[i] - '0') != (t[i] - '0')) sum[i]++;
	}
	for (int i = n;i >= 1;i--){
		if ((t[i] - '0') != 0 && check(i)){
			dot = i;
			break;
		}
	}
	if (dot == -1e9){
		clear();
		cout << -1 << "\n";
		return;
	}
	k -= sum[dot - 1];
	for (int i = 1;i <= n;i++){
		if (i < dot) cout << ((t[i] - '0'));
		else if (i == dot){
			if ((t[i] - '0' - 1) == (s[i] - '0')){
				if (n - i >= k) cout << s[i] - '0';
				else{
					k--;
					cout << s[i] - '0' - 1;
				}
				continue;
			}
			if (k){
				cout << (t[i] - '0' - 1);
				k--;
			}
			else cout << (s[i] - '0');
		}
		else{
			if (k){
				if ((s[i] == '9')){
					if (n - i >= k) cout << 9;
					else cout << 8,k--;
				}
				else cout << 9,k--;
			}
			else cout << (s[i] - '0');
		} 
	}
	cout << "\n";
	clear();
}
int main(){
	int T;
	cin >> T;
	while (T--) solve();
}
/*
1
11046 00097 4
*/

---

