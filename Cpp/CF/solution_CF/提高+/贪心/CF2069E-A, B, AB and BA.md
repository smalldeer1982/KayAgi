# A, B, AB and BA

## 题目描述

给定一个由字符 A 和 B 组成的字符串 $s$。

你的任务是将它分割成长度为 $1$ 或 $2$ 的块，使得：
- "A" 类型的块数量不超过 $a$；
- "B" 类型的块数量不超过 $b$；
- "AB" 类型的块数量不超过 $ab$；
- "BA" 类型的块数量不超过 $ba$；

其中 "AA" 和 "BB" 类型的块是被禁止的。原始字符串 $s$ 的每个字符必须恰好属于一个块。

## 说明/提示

第三个测试用例中，所有可能的分割方式为：A|B|A、AB|A 或 A|BA。所有这些方式都至少包含一个 "A"。

第四个测试用例中，一种可能的分割方式是：A|B|B|A|B|A|A|B。

第五个测试用例中，一种可能的分割方式是：A|BA|B|BA|AB|BA|AB。

翻译由 DeepSeek R1 完成

## 样例 #1

### 输入

```
7
A
0 0 10 10
B
0 1 0 0
ABA
0 0 1 1
ABBABAAB
5 5 0 0
ABABBAABBAAB
1 1 2 3
ABBBBAB
0 3 2 0
BAABBA
1 3 2 0```

### 输出

```
NO
YES
NO
YES
YES
YES
NO```

# 题解

## 作者：chenxi2009 (赞：8)

## 思路
$n\leftarrow\vert s\vert$。我们先把整个 $s$ 全部划分为长度为 $1$ 的串，即 `A` 和 `B`。\
此时若 `A` 的数量 $cnt_a>a$，或 `B` 的数量 $cnt_b>b$，我们就需要合并相邻的 `A`、`B`，构成 `AB` 或 `BA`。这两种新子串都可以减少一个 `A` 和一个 `B`，所以它们的数量总和至少得是 $\max(cnt_a-a,cnt_b-b)$。接下来考虑怎么尽可能多地合并出 `AB` 和 `BA`。

我们用连续的 `A` 和连续的 `B` 为分界（因为它们不能参与合并），可以把 $s$ 划分成几个内部合并会互相影响的子串。有如下形式：`ABABAB...ABA`、`BABABA...BAB`、`ABAB...AB`、`BABAB...A`。

令子串长度为 $l$，发现前两种是可以划分出 $\left\lfloor\frac{l}{2}\right\rfloor$ 个 `AB` 或 `BA` 的（暂不考虑 `AB` 或 `BA` 数量超限的情况）；\
第三种可以划分成 $\frac{l}{2}$ 个 `AB`，但是内部十分紧凑，如果要划分出 `BA` 的话只能划分出 $\frac{l}{2}-1$ 个 `AB` 或 `BA`；\
第四种和第三种类似，可以划分成 $\frac{l}{2}$ 个 `BA`，或 $\frac{l}{2}-1$ 个 `AB` 或 `BA`。

考虑贪心，前两者怎么用都没有损失，先保留，考虑后两者；第三种肯定优先拆 `AB` 直至数量达到 $ab$，由于**每有一个子串被分出了 `BA` 就会出现 $1$ 的损失**，我们优先让短的子串被拆成 `AB`，这样在限制 `AB` 的数量时，可以让更多的子串被**纯净地**拆分，损失更小。\
同理第四种子串也优先拿出短的拆成 `BA`，剩下的没拆完的子串才考虑 `AB`。

我们前面留下的前两种子串这个时候再来用。如果说最终拼出来的 `AB` 和 `BA` 的数量和 $\ge\max(cnt_a-a,cnt_b-b)$ 就是成功的，否则失败。

由于需要优先拿短的子串所以有一个排序过程，时间复杂度 $O(\sum\vert s\vert\log\vert s\vert)$。
## 代码
```cpp
#include<bits/stdc++.h>
using namespace std;
int T,n,a,b,c,d,cnta,cntb,cnt,trn,l,tmp;
char s[600000];
vector<int>vc,vd;
int main(){
	scanf("%d",&T);
	while(T --){
		scanf("%s%d%d%d%d",s + 1,&a,&b,&c,&d);
		vc.clear(),vd.clear(),cnta = cntb = cnt = 0,l = 1,n = strlen(s + 1);
		for(int i = 1;i <= n;i ++){
			if(s[i] == 'A') cnta ++;//统计 A 和 B 的数量 
			else cntb ++;     
		}
		trn = max(cnta - a,cntb - b);//我们需要这么多的 AB 或 BA 
		for(int i = 1;i <= n;i ++){
			if(i == n || s[i] == s[i + 1]){
				tmp = (i - l + 1) / 2;
				if(tmp){
					if(s[l] == s[i]) cnt += tmp;//前两种子串，可以任意分成 tmp 个 AB 或 BA 
					else if(s[l] == 'A') vc.push_back(tmp);//第三种子串，可以分成 tmp/2 个 AB 或 tmp/2-1 个 AB 或 BA 
					else vd.push_back(tmp);//第四种子串 
				}
				l = i + 1;
			}
		}
		sort(vc.begin(),vc.end());//排序，优先用小的 
		sort(vd.begin(),vd.end());
		for(auto i : vc){
			if(c < i) cnt += i - 1;//要超限了，可以分成 i-1 个 AB 或 BA 
			else trn -= i,c -= i;//不会超限，就组成 i 个 AB 
		} 
		for(auto i : vd){
			if(d < i) trn -= d,i -= d,d = 0,cnt += i - 1;
			else trn -= i,d -= i;
		} 
		if(trn <= min(c + d,cnt)) printf("YES\n");//还有 cnt 个任意组成 AB 或 BA 的机会 
		else printf("NO\n");
	}
	return 0;
} 
```

---

## 作者：do_it_tomorrow (赞：2)

对于连续的 $\texttt{AA}$ 和 $\texttt{BB}$ 无法处理，先把这个东西拆开。

因为 $ab$ 和 $ba$ 可以完成的 $a$ 和 $b$ 都是都是可以完成的，所以我们显然可以先贪心的选择 $ab$ 和 $ba$。

考虑对于长度不同的段分开考虑：

对于偶数段，我们可以全部使用 $ab$ 或者 $ba$，也可以使用 $a,b$ 之后把 $ab$ 和 $ba$ 一起使用。

对于奇数段，我们必须使用一个 $a$ 或者 $b$ 然后把 $ab$ 和 $ba$ 一起使用。

显然奇数段的情况是确定的，而偶数段有更多操作的空间，那么先操作偶数段。

直接模拟即可，时间复杂度为 $O(\sum n)$。

[Submission #316060112 - Codeforces](https://codeforces.com/contest/2069/submission/316060112)

~~自认为实现很优雅~~。

---

## 作者：HD0X (赞：2)

题意略。

显然，$a$ 和 $b$ 更“稀有”，因为它们可以填补所有类型的字符串，所以考虑如何更好使用 $ab$ 和 $ba$。

首先，我们先将 $\text{AAA}$ 或 $\text{BBB}$ 中间的那一个用 $a$ 和 $b$ 删掉（左右是空也行），因为它们一定只能被单独删掉。剩下的串分为 $\text{4}$ 种： $\text{ABA}$，$\text{ABAB}$，$\text{BAB}$，$\text{BABA}$。

首先分析 $\text{2 4}$ 两种，最好肯定都用自己的循环来填满，如果填不满，就在用完后剩下的串上操作。

具体的：对于 $\text{ABABABAB}$ ，令 $ab=2$，先用完两次使其变成 $\text{ABAB}$，再在开头用 $a$，结尾用 $b$，使串变为 $BA$，就可以用 $ba$ 去做，如果 $ba$ 也不够了，再用 $a$ 和 $b$ 去做。如果 $\frac{len} 2 \le ab$，就直接用 $ab$ 做。

为了尽量使 $a$ 和 $b$ 的消耗变少，我们希望尽量多的串可以用自己的循环解决，所以我们按长度从小到大依次处理，$\text{BABA}$ 同理。

再分析 $\text{1 3}$ 两种，它们一定会用一个开头的字母，但是用的位置使得它们可以决定 $ab$ 和 $ba$ 的分配比例，例如 $\text{ABABABA}$，在结尾用一个 $a$ 就可以全用 $ab$，在开头用一个 $a$ 就可以全用 $ba$，如果在中间用就可以自由分配 $ab$ 和 $ba$ 的用量。所以说先用 $a$ 减去 $cnt_1$，用 $b$ 减去 $cnt_3$，再用两种串长度之和的一半减去余下的 $ab$ 和 $ba$ 的数量，剩下的就用 $a$ 和 $b$个减去剩下的组数即可。

[代码](https://codeforces.com/contest/2069/submission/306743417)

---

## 作者：carboxylBase (赞：2)

[题面](https://codeforces.com/contest/2069/problem/E)

首先，注意到每选择一个 AB 或 BA ，我们需要的 A 和 B 的数量都会减一，选的 AB 或 BA 越多，就越容易满足 A 和 B 的数量限制。因此，本题实质上就是在问我们最多可以选择出多少个 AB 和 BA 。

实际上，字符串 S 仅由以下两种形式的子串构成：
+ ABABA型。特征是长度为奇数，A 和 B 交替排列。设其长度为 $len$ ，那么我们可以从中构造出至多 $(len - 1) / 2$ 个 AB 和 BA。
+ ABAB型。特征是长度为偶数，A 和 B 交替排列。设首字母为 A ，长度设为 $len$ ，那么我们至多从中构造出 $len / 2$ 个 AB ，或者 $(len - 1) / 2$ 个 BA 。当然我们也可以将其部分转换为 AB ，部分转换为 BA 。首字母为 B 的同理分析。

由于 `AA`、`BB` 这种是不合法的，所以我们不妨按照上面提及的两种形式，对 S 进行分割。以 `ABABBBABBA` 为例，将其分割为 `ABAB\B\BAB\BA`，得到若干子串。下面考虑如何贪心。

首先，长度为奇数的子串应当最后考虑，因为它转换为 AB 或者 BA 的数量是一样的。

对于长度为偶数的子串，以 A 开头的子串为例。上文提到，相较于 BA ，此类子串可以转换出更多的 AB ，因此，我们自然希望它尽可能多的转换为 AB 。可是 AB 的容量也许是不够的，多出来的子串应当被转换成 BA 才能保证结果最优。怎样才能转换出尽可能多的 BA 呢？

（此段落中子串均指长度为偶，首字母为 A 的子串）模拟一下子串转换 AB 的过程。`ABABAB`，`ABAB`，`AB` 分别可以转换出 2，1，0 个 BA，我们将 `ABABAB` 的前两位转换为 AB 后，剩余部分只能转换出 1 个 BA，减少 1 个；对 `ABAB` 同样操作，剩余部分只能转换出 0 个 BA ，减少 1 个；对 `AB` 同样操作，剩余部分可以转换出 0 个 BA，减少了 0 个。发现规律了吗？只有 `AB` 在上述变换后转换量减少了 0 ，因为它的转换量本身就是 0 ！所以转换 `AB` 是没有损失的！因此，贪心地想，我们应当优先将长度小的子串转换为 AB ，这样可以保证多出来的子串能构造出尽可能多的 BA 。直接把子串按长度排序，然后从短向长选即可。

最后，我们将根据 AB 和 BA 容量的剩余情况，将剩余的奇数长度子串转换为 AB 或者 BA 。

设共转换出 $cnt\_ab$ 个 AB 或 BA ，S 含有 $cnt\_a$ 个 A 和 $cnt\_b$ 个 B 。记 A 容量为 $V_a$, B 容量为 $V_b$ 。若下面两式成立则答案为 `YES`

$$cnt\_a - cnt\_ab \leq V_a $$
$$ cnt\_b - cnt\_ab \leq V_b$$

代码：
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define DEBUG 1
const ll N = 2000000;
const ll MOD = 998244353;
const ll MAX = 1e18;

string s;
int a,b,ab,ba;

void solve(){
    cin >> s >> a >> b >> ab >> ba;
    int n = s.length();
    s = "s" + s;

    int cntA = 0,cntB = 0,cnt_ab = 0;

    for (int i = 1;i<n+1;i++){
        if (s[i] == 'A'){
            cntA++;
        }else{
            cntB++;
        }
    }    

    char c = s[1];
    int len = 1;

    vector<int> odd;
    vector<int> A,B;

    for (int i = 2;i<n+1;i++){
        if (s[i] != s[i-1]){
            len++;
        }else{
            if (len & 1){
                if (len > 1){
                    odd.push_back(len);
                }
            }else{
                if (c == 'A'){
                    A.push_back(len);
                }else{
                    B.push_back(len);
                }
            }
            len = 1;
            c = s[i];
        }
    }

    if (len & 1){
        if (len > 1){
            odd.push_back(len);
        }
    }else{
        if (c == 'A'){
            A.push_back(len);
        }else{
            B.push_back(len);
        }
    }

    int AB = ab,BA = ba;

    sort(A.begin(),A.end());
    sort(B.begin(),B.end());

    for (int i = 0;i<A.size() && ab;i++){
        if (ab >= A[i] / 2){
            ab -= A[i] / 2;
            A[i] = 0;
        }else{
            A[i] -= ab * 2;
            ab = 0;
        }
    }
    for (int i = 0;i<B.size() && ba;i++){
        if (ba >= B[i] / 2){
            ba -= B[i] / 2;
            B[i] = 0;
        }else{
            B[i] -= ba * 2;
            ba = 0;
        }
    }

    if (ab > 0){
        for (int i = 0;i<B.size();i++){
            if (ab >= (B[i] - 1) / 2){
                ab -= (B[i] - 1) / 2;
            }else{
                ab = 0;
            }
        }
    }

    if (ba > 0){
        for (int i = 0;i<A.size();i++){
            if (ba >= (A[i] - 1) / 2){
                ba -= (A[i] - 1) / 2;
            }else{
                ba = 0;
            }
        }
    }

    if (ab > 0){
        for (int j = 0;j<odd.size() && ab > 0;j++){
            if (ab > odd[j] / 2){
                ab -= odd[j] / 2;
                cnt_ab += odd[j] / 2;
                odd[j] = 1;
            }else{
                odd[j] -= ab * 2;
                cnt_ab += ab;
                ab = 0;
                break;
            }
        }
    }

    if (ba > 0){
        for (int j = 0;j<odd.size() && ba > 0;j++){
            if (ba > odd[j] / 2){
                ba -= odd[j] / 2;
                cnt_ab += odd[j] / 2;
                odd[j] = 1;
            }else{
                odd[j] -= ba * 2;
                cnt_ab += ba;
                ba = 0;
                break;
            }
        }
    }

    cnt_ab = AB - ab + BA - ba;
    if (cntA - cnt_ab <= a && cntB - cnt_ab <= b){
        cout << "YES" << endl;
    }else{
        cout << "NO" << endl;
    }
    return;
}

signed main(){
    ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    int _ = 1;
    cin >> _;
    while (_--){
        solve();
    }
    return 0;
}
```

---

## 作者：xxr___ (赞：1)

$2300$ 的思维题确实高质量。

设 $p$ 表示 $S$ 中 $A$ 出现的次数，设 $q$ 表示 $S$ 中 $B$ 出现的次数。

如果 $p \leq a$ 且 $q\leq b$ 那么可以直接用 `A` 和 `B` 来覆盖。

否则，我们发现每次不管进行 $AB$ 操作，还是 $BA$ 操作，都会同时可以少使用一个 $A$ 和一个 $B$ 操作。

那么说明，如果我们想覆盖完，至少需要进行 $need = \max (p - a,q - b)$ 次 $AB$ 或者 $BA$ 操作。

那么接下来就很简单了，我们发现现在可以使用 $AB$ 操作，或者使用 $BA$ 操作组成的子串只有以下几种情况：
1. 形容 $ABAB...A$ 这种或者是 $BABA...B$ 的，这两种类型是首位相同，且 $A$ 和 $B$ 交错排放的，且长度是奇数。
2. 形容 $ABA...AB$ 这种或者是 $BAB...BA$ 的，这两种类型是由 $AB$ 通过不停地复制拼接成的，且长度是偶数。

那么这两种类型的串有哪些特点呢，我们来分析下：
1. 对于第一种串，显然无论你选哪种，$AB$ 也好 $BA$ 也好，或者都选，都能选出来 $\lfloor \frac{|s|}{2}\rfloor$ 这是定值，手动模拟一下可以发现。
2. 对于第二种串，有两种情况：
     - 如果是 $ABA...AB$ 的，那么选 $AB$ 显然是最优的，可以选 $\frac{|s|}{2}$ 个 $AB$。但是如果想要只选 $BA$ 或者两者都选，那么只能最多选 $\frac{|s|}{2} - 1$ 个，手动模拟一下也是可以发现的。
     - 如果是 $BAB...BA$ 那么和上面的其实同理，只不过这个时候选 $BA$ 变成了最优的策略。

好，事已至此，问题基本已经得以解决，我们考虑怎么来最优的选择哪些地方覆盖上 $AB$ 哪些地方覆盖上 $BA$。

首先，我们定义 $cnt$ 表示可以随便用的有多少个位置，也就是既能用 $AB$ 也能用 $BA$ 覆盖的串。

对于第一种类型的串，它随便放，直接让 $cnt → cnt + \sum \lfloor \frac{|s|}{2}\rfloor$ 即可。

然后遍历第二种类型的第一种类型的串，尽量放 $AB$ 多出来的留着放 $BA$，同时修改 $need → need - \frac{|s|}{2}$。

遍历第二种类型的第二种类型的串，尽量放 $BA$ 多出来的放 $AB$，修改 $need$。

这里应该按照大小从小到大的顺序来枚举，因为这样能尽量可能的多铺满自己这个类型的，少浪费自己的类型去置换另一个类型，具体看代码，这里不好描述。

最后判断一下剩余需要的覆盖次数 $need$ 和可以随便放的次数就行了。

[代码](https://codeforces.com/problemset/submission/2069/315259862)

---

## 作者：yvbf (赞：0)

![](bilibili:BV1DkAzetEX9?t=1807)

---

