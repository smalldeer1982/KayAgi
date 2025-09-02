# [Aya Round 1 F] 琪露诺的选择题

## 题目背景

**Problem Number:** [$\textit{24}$](https://www.luogu.com.cn/training/1392)

在经过射命丸文的一番调教之后，琪露诺的智商总算增长了⑨点。

现在寺子屋又要开始考试了，琪露诺通过一些手段知道了答案中的一些信息，而且因为她冰雪聪明，她不希望自己的成绩进步太明显，从而被老师上白泽慧音特别关照。因此她找到了你寻求一些帮助。

（注意：考试作弊是不对的！）

## 题目描述

有 $2\cdot n$ 道选择题，每题有 $\text{A}$ 和 $\text{B}$ 两个选项。正确答案可以表示为一个长度为 $2\cdot n$ 的字符串。

现在你要构造出一份作答（长度同样为 $2\cdot n$ 的字符串），其中**恰好**有 $a$ 个 $\text{A}$，同时与正确答案相比，你的作答恰好有 $e$ 个错误。如果不存在这样的构造方案，报告无解。

**注意：为了方便处理，本题保证 $e\le n$。**

**形式化地**，给定 $n,a,e$ 和一个长度为 $2\cdot n$ 的 01 串 $s$，你需要构造出一个恰好有 $a$ 个字符是 $\texttt 0$ 的长度为 $2\cdot n$ 的 01 串 $p$，使得

$$
\left(\sum_{i=1}^{2\cdot n}[s_i\ne p_i]\right)=e,
$$

其中 $[]$ 是 Iverson Bracket，详见「**说明/提示**」中的「提示」。

## 说明/提示

### 样例解释

对于数据 $1$，你构造出的作答串 $\text{BB{\color{e74c3c}AA}BB}$ 中恰好有 $2$ 个 $\text A$，与答案串相比刚好有 $3$ 处不同（即，有 $3$ 处错误）：

$$
\text{{\color{e74c3c}A}BA{\color{e74c3c}B}B{\color{e74c3c}A}}\\
\text{{\color{52c41a}B}BA{\color{52c41a}A}B{\color{52c41a}B}}
$$

故符合要求。

对于数据 $2$，不存在合法构造方案。

### 数据规模与约定

对于 $100\%$ 的数据，有 $1\le T\le 100$，$1\le n\le 10^5$，$0\le e\le n$，$0\le a\le 2\cdot n$。

单组测试点内保证 $\sum(2\cdot n)\le 10^6$。

### 提示

$\textbf{A. Iverson Bracket}$

Iverson Bracket，是一种用方括号记号，如果方括号内的条件满足则为 $1$，不满足则为 $0$。更确切地讲，

$$
[P]=\begin{cases}1, & \text{If }P\text{ is true,}\\0,&\text{Otherwise.}\end{cases}
$$

## 样例 #1

### 输入

```
2
3 2 3
ABABBA
3 3 1
AAABBB```

### 输出

```
BBAABB
-1```

# 题解

## 作者：CSP_Sept (赞：12)

# 琪露诺的选择题

考虑到我们可以先固定一定数量的 $\texttt A$，然后进行交换操作，这样省去了构造时的一个麻烦。

接下来注意到每次交换操作必定只会影响到**偶数**个答案的变更，单次交换只会让错误增加或减少 $2$ 个。

由于不想让减少占用讨论空间，发现初始固定状态下使错误数量最小即可让错误变化退化为仅增加。

于是先尽量使得固定状态下的错误数量最小，记为 $r$。将 $e$ 减去 $r$ 得到 $e'$，即为接下来需要产生的错误数量。

分别统计出 A,B 位置正确的数量，两者取 $\min$，即得到最大交换数量 $x$。

由上述讨论发现，当 $e'\equiv1\pmod2,e'>2x,e'<0$ 三者有一种成立即为无解。

有解的情况，交换 $\dfrac{e'}2$ 次正确的 $\texttt{A,B}$ 即可，在输出时稍加统计即可 $O(n)$ 做到。

```cpp
#include <cstdio>
#include <algorithm>

#define N 200010
using namespace std;
int n, a, e;
char s[N];
int p[N];
void Solve(){
    scanf("%d%d%d", &n, &a, &e);
    int m = n << 1, b = m - a;
    int x = 0, y = 0;
    scanf("%s", s + 1);
    int r = 0;
    for(int i = 1 ; i <= m ; i++){
        if(s[i] == 'A'){
            if(a == 0)
                p[i] = 1, r++;
            else
                p[i] = 0, a--, x++;
        }
        if(s[i] == 'B'){
            if(b == 0)
                p[i] = 0, r++;
            else
                p[i] = 1, b--, y++;
        }
    }
    e -= r; int opx = min(x, y);
    int opa, opb;
    if(e < 0 || e & 1 || e > 2 * opx){
        puts("-1");
        return;
    }
    else opa = opb = (e >> 1);
    for(int i = 1 ; i <= m ; i++){
        if(p[i] + 'A' == s[i]){
            if(p[i] == 0){
                if(opa){printf("B"); opa--;}
                else printf("A");
            }
            else if(p[i] == 1){
                if(opb){printf("A"); opb--;}
                else printf("B");
            }
        }
        else printf("%c", p[i] + 'A');
    }
    puts("");
}
int main(){
    int T;
    scanf("%d", &T);
    while(T--)
        Solve();
    return 0;
}
```

---

## 作者：sixrc (赞：10)

前置知识：小学和差问题（）

设答案串与原串对应位置都为 $\texttt{A}$ 的数量为 $p$；答案串为 $\texttt{A}$，原串对应位置为 $\texttt{B}$ 的数量为 $q$。记原串中 $\texttt{A}$ 的数量为 $sa$，原串中 $\texttt{B}$ 的数量为 $sb$。

可以列出方程：

$$p+q=a,sa-p+q=e$$

$$\to q+p=a,q-p=e-sa$$

只需将两式相加相减即可求出 $p,q$。最后输出时判断，在原串为 $\texttt{A}$ 的对应位置上先输出完了 $p$ 个 $\texttt{A}$，再输出 $\texttt{B}$；原串为 $\texttt{B}$ 的对应位置同理。

但是解得的 $p,q$ 不一定合法，需要满足如下条件才合法：

- $0 \le p \le \min(sa,e)$

- $0 \le q \le \min(sb,e)$

- $p,q$ 为正**整数**。

特判即可。

### Code：

```c++
#include <bits/stdc++.h>
using namespace std;
int T, n, na, e, sa, sb, p, q;
char s[200010];
int main(){
	scanf ("%d", &T);
	while (T --){
		scanf ("%d%d%d%s", &n, &na, &e, s+1);
		sa = 0, sb = 0;
		int len = n * 2;
		for (int i=1; i<=len; i++){
			if (s[i] == 'A') sa ++;
			else sb ++; 
		}
		int sum = e - sa + na;
		if (sum & 1){
			puts ("-1");
			continue;
		}
		q = sum / 2, p = (na - e + sa) / 2;
		if (p < 0 || q < 0 || p > min(na, sa) || q > min(na, sb)){
			puts ("-1");
			continue;
		}
		for (int i=1; i<=len; i++){
			if (s[i] == 'A'){
				if (p) printf ("A"), p --;
				else printf ("B");
			}
			else{
				if (q) printf ("A"), q --;
				else printf ("B");
			}
		}
		puts ("");
	}
	return 0;
}

```

---

## 作者：olegekei (赞：7)

~~最开始把题目里的e读成正确数量了，改了好久改不对~~

考虑二分，枚举需要将几个A填到B的位置(就可以使错误数量+2)，然后判断二分出的答案是否与e相等且原串中AB的数量满足 $A>l$，$B>r$ 即可

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a,e;
char s[200030];//答案串，记得开2倍
int vis[2];//vis[0]为A的数量，vis[1]为B的数量
int check(int x){//二分跑出来的x来check
	int now=vis[1]-x;//now为剩下的作为正确答案的B
	int cnt=now+(a-x);//a-x为剩下的作为正确答案的A
	return cnt;//两者之和为正确答案数量
}
int main(){
ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
int t;
cin>>t;
while(t--){
	vis[0]=vis[1]=0;//初始化
	cin>>n>>a>>e;
	e=2*n-e;//题目读错了，把e处理一下
    //↑↑↑↑↑↑↑↑↑↑↑↑此处的e记录的是正确答案的数量
	for(int i=1;i<=2*n;i++){
		cin>>s[i];//读入选择题正确答案
		vis[s[i]-'A']++;//统计A与B的个数
	}
	int l=0,r=a;
	while(l<=r){
		int mid=l+r>>1;
		if(check(mid)>=e)l=mid+1;
		else r=mid-1;
	}//二分过程
	if(check(r)!=e){cout<<-1<<'\n';continue;}
   //如果最后二分得到的答案不与e匹配则无解
	l=a-r;
	if(l>vis[0]||r>vis[1]){cout<<-1<<'\n';continue;}
   //原串中A与B的数量不足以支持l与r的操作也无解
//-------节省空间没记录答案串，根据原串输出即可-------
//此刻r记录需要有几个B换成A，
//l记录需要有几个A保持A
	int i=1;
	while(l&&r){//两者皆大于0，直接输出A即可
		cout<<'A';
		if(s[i]=='A')l--;//根据情况处理l和r
		else r--;
		i++;
	}
	while(l){//l有剩余
		if(s[i]=='A'){l--;cout<<'A';}
		else cout<<'B';
		i++;
	}
	while(r){//r有剩余
		if(s[i]=='B'){r--;cout<<'A';}
		else cout<<'B';
		i++;
	}
	while(i<=2*n){//最后输出剩下的B即可
		cout<<'B';
		i++;
	}
	cout<<'\n';
	
}
return 0;//结束程序
}
```


---

## 作者：NightTide (赞：5)

## PART 0：前排警告
这是一篇很诡异且码量极大的题解，但不需要脑子，请谨慎食用。
## PART 1: 解题思路
>Q：为什么没有题目大意
>
>A：因为它真的很明了，不是吗？

#### 一些定义
在这篇题解中，我们定义 $a_0$ 表示原来的答案中 `'A'` 的个数，。其他变量如 $a$，$e$ 等都和题目描述中相同。下文所说 **"条件一"** 表示题目中对 `'A'` 的个数的要求，**"条件二"** 则表示目中对错误答案的个数的要求。

----

题目中给了两个限制，所以我们可以考虑依次满足两个条件。先来分类讨论。

1. 若 $a_0 < a$

	这说明我们需要添加一些字符 `'A'` 来满足条件一，我们设需要添加的数量为 $d$。
    
    接下来继续分类讨论：
    
    1. 若 $e < d$
    
    	这 $d$ 个新的字符 `'A'` 自然会增加错误的个数，至少会增加 $d$ 个，所以，如果 $e < d$，那么显然是无解的。
    	
    2. 若 $d < e$
    	
    	这样的话，我们在把 $d$ 个 `'B'` 改称 `'A'` 之后还没有达到条件二需要的错误个数，我们设剩下的错误个数为 $f$。
        
        考虑如何在不改变 `'A'` 的个数的情况下来增加错误的个数。显然，我们只能把原来的 `'A'` 和 `'B'` 交换，这样一次性会增加两个错误，所以只有 $2|f$ 的时候才有解，否则是无解的。
        
        注意，只有把原来的答案中的 `'A'` 和 `'B'` 交换才能够增加错误，新增的 `'A'` 与 `'B'` 交换是不会增加错误的，所以我们可以先交换原来的 `'A'` 和 `'B'`，再把 $d$ 个 `'B'` 改称 `'A'` 。
        ```cpp
        if((e - (a - ca)) % 2){
            printf("-1\n");
            continue;
        }else if((e - (a - ca)) / 2 + a - ca > 2 * n - ca || (e - (a - ca)) / 2 > ca){
            printf("-1\n");
            continue;
        }else{
            bool flag = true;
            int tmp = (e - (a - ca)) / 2;
            vector<int> posa, posb;// 分别表示原来的答案中 'A' 的位置和 'B' 的位置
            for(int i = 1; i <= n * 2; i++){
                if(ans[i] == 'A') posa.push_back(i);
                else posb.push_back(i);
            }
            for(int i = 1; i <= tmp; i++){
                if(posa.empty() || posb.empty()){
                    // 如果当前还没有达到应有的交换次数就交换失败了，那么无解
                    printf("-1\n");
                    flag = false;
                    break;
                }
                int xa = posa.back(), xb = posb.back();
                posa.pop_back(); posb.pop_back();
                swap(ans[xa], ans[xb]);// 交换
            }
            if(!flag) continue;
            tmp = a - ca;
            // 接下来把一些 'B' 更改成 'A' 来满足条件
            if(posb.size() < tmp){// 如果可供修改的 'B' 达不到要求，无解
                printf("-1\n");
                continue;
            }else{
                // 修改
                for(int i = 0; i < tmp; i++) ans[posb[i]] = 'A';
            }
        }
          ```
    3. 若 $e = d$
    	此时我们只需要增添 $d$ 个 `'A'` 就能够恰好满足条件一和条件二，直接修改即可。
        ```cpp
        int tmp = e;
        for(int i = 1; i <= n * 2 && tmp; i++){
            if(ans[i] == 'B'){
                ans[i] = 'A';
                tmp--;
            }
        }
        ```
2. 若 $a_0 > a$

	此时 `'A'` 的数量超出了条件需要的范围，需要修改一些 `'A'` 为 `'B'`。我们同样设需要修改的数量为 $d$。
    
    1. $d > e$
    	
        和上面的情况相同，在满足条件一之后必然会超过条件二的限制，无解
    2. $d < e$
    	
        也和之前的类似，在修改完 $b$ 个超出限制的 `'A'` 之后还需要更多的错误，我们的策略也和之前相似，这里不再赘述。
        
        ```cpp
        if((e - (ca - a)) % 2){
            printf("-1\n");
            continue;
        }else if((e - (ca - a)) / 2 + ca - a > ca || (e - (ca - a)) / 2 > 2 * n - ca){
            printf("-1\n");
            continue;
        }else{
            bool flag = true;
            int tmp = (e - (ca - a)) / 2;
            vector<int> posa, posb;// 分别表示原来的答案中 'A' 的位置和 'B' 的位置
            for(int i = 1; i <= n * 2; i++){
                if(ans[i] == 'A') posa.push_back(i);
                else posb.push_back(i);
            }
            for(int i = 1; i <= tmp; i++){
                if(posa.empty() || posb.empty()){
                    // 如果当前还没有达到应有的交换次数就交换失败了，那么无解
                    printf("-1\n");
                    flag = false;
                    break;
                }
                int xa = posa.back(), xb = posb.back();
                posa.pop_back(); posb.pop_back();
                swap(ans[xa], ans[xb]);// 交换
            }
            if(!flag) continue;
            tmp = ca - a;
            // 接下来把一些 'A' 更改成 'B' 来满足条件
            if(posa.size() < tmp){// 如果可供修改的 'A' 达不到要求，无解
                printf("-1\n");
                continue;
            }else{
                // 修改
                for(int i = 0; i < tmp; i++) ans[posa[i]] = 'B';
            }
			```
	3. 若 $e = d$
    	
    	此时我们只需要修改 $d$ 个 `'A'` 就能够恰好满足条件一和条件二，直接修改即可。
        ```cpp
        int tmp = e;
        for(int i = 1; i <= n * 2 && tmp; i++){
            if(ans[i] == 'A'){
                ans[i] = 'B';
                tmp--;
            }
        }
        ```
3. $a_0 = a$

	这种情况下就只能够通过交换来满足限制二，这里的交换和前面的是一样的：
	```cpp
    if(e % 2){
        printf("-1\n");
        continue;
    }else{
        bool flag = true;
        int tmp = (e - (a - ca)) / 2;
        vector<int> posa, posb;
        for(int i = 1; i <= n * 2; i++){
            if(ans[i] == 'A') posa.push_back(i);
            else posb.push_back(i);
        }
        for(int i = 1; i <= tmp; i++){
            if(posa.empty() || posb.empty()){
                printf("-1");
                flag = false;
                break;
            }
            int xa = posa.back(), xb = posb.back();
            posa.pop_back(); posb.pop_back();
            swap(ans[xa], ans[xb]);
        }
        if(!flag){
            printf("-1\n");
            continue;
        }
    }
    ```

分来讨论完毕。（已经这么长了吗？如果想看作者赛时心路历程的可以前往文末）

## PART 2：完整代码
$145$ 行巨型代码奉上：

```cpp
#include<bits/stdc++.h>
#define MAXN 100010
using namespace std;
int t, n, a, ca, e;
char ans[MAXN << 1];
int main(){
    scanf("%d",&t);
    while(t--){
        scanf("%d%d%d",&n,&a,&e);
        scanf("%s",ans + 1);
        ca = 0;
        for(int i = 1; i <= n * 2; i++) ca += (ans[i] == 'A');
        if(ca > a){
            if(ca - a < e){
                if((e - (ca - a)) % 2){
                    printf("-1\n");
                    continue;
                }else if((e - (ca - a)) / 2 + ca - a > ca || (e - (ca - a)) / 2 > 2 * n - ca){
                    printf("-1\n");
                    continue;
                }else{
                    bool flag = true;
                    int tmp = (e - (ca - a)) / 2;
                    vector<int> posa, posb;// 分别表示原来的答案中 'A' 的位置和 'B' 的位置
                    for(int i = 1; i <= n * 2; i++){
                        if(ans[i] == 'A') posa.push_back(i);
                        else posb.push_back(i);
                    }
                    for(int i = 1; i <= tmp; i++){
                        if(posa.empty() || posb.empty()){
                            // 如果当前还没有达到应有的交换次数就交换失败了，那么无解
                            printf("-1\n");
                            flag = false;
                            break;
                        }
                        int xa = posa.back(), xb = posb.back();
                        posa.pop_back(); posb.pop_back();
                        swap(ans[xa], ans[xb]);// 交换
                    }
                    if(!flag) continue;
                    tmp = ca - a;
                    // 接下来把一些 'A' 更改成 'B' 来满足条件
                    if(posa.size() < tmp){// 如果可供修改的 'A' 达不到要求，无解
                        printf("-1\n");
                        continue;
                    }else{
                        // 修改
                        for(int i = 0; i < tmp; i++) ans[posa[i]] = 'B';
                    }
                }
            }else if(ca - a == e){
                int tmp = e;
                for(int i = 1; i <= n * 2 && tmp; i++){
                    if(ans[i] == 'A'){
                        ans[i] = 'B';
                        tmp--;
                    }
                }
            }else{
                printf("-1\n");
                continue;
            }
        }else if(a > ca){
            if(a - ca == e){
                int tmp = e;
                for(int i = 1; i <= n * 2 && tmp; i++){
                    if(ans[i] == 'B'){
                        ans[i] = 'A';
                        tmp--;
                    }
                }
            }else if(a - ca > e){
                printf("-1\n");
                continue;
            }else{
                if((e - (a - ca)) % 2){
                    printf("-1\n");
                    continue;
                }else if((e - (a - ca)) / 2 + a - ca > 2 * n - ca || (e - (a - ca)) / 2 > ca){
                    printf("-1\n");
                    continue;
                }else{
                    bool flag = true;
                    int tmp = (e - (a - ca)) / 2;
                    vector<int> posa, posb;// 分别表示原来的答案中 'A' 的位置和 'B' 的位置
                    for(int i = 1; i <= n * 2; i++){
                        if(ans[i] == 'A') posa.push_back(i);
                        else posb.push_back(i);
                    }
                    for(int i = 1; i <= tmp; i++){
                        if(posa.empty() || posb.empty()){
                            // 如果当前还没有达到应有的交换次数就交换失败了，那么无解
                            printf("-1\n");
                            flag = false;
                            break;
                        }
                        int xa = posa.back(), xb = posb.back();
                        posa.pop_back(); posb.pop_back();
                        swap(ans[xa], ans[xb]);// 交换
                    }
                    if(!flag) continue;
                    tmp = a - ca;
                    // 接下来把一些 'B' 更改成 'A' 来满足条件
                    if(posb.size() < tmp){// 如果可供修改的 'B' 达不到要求，无解
                        printf("-1\n");
                        continue;
                    }else{
                        // 修改
                        for(int i = 0; i < tmp; i++) ans[posb[i]] = 'A';
                    }
                }
            }
        }else if(a == ca){
            if(e % 2){
                printf("-1\n");
                continue;
            }else{
                bool flag = true;
                int tmp = (e - (a - ca)) / 2;
                vector<int> posa, posb;
                for(int i = 1; i <= n * 2; i++){
                    if(ans[i] == 'A') posa.push_back(i);
                    else posb.push_back(i);
                }
                for(int i = 1; i <= tmp; i++){
                    if(posa.empty() || posb.empty()){
                        printf("-1");
                        flag = false;
                        break;
                    }
                    int xa = posa.back(), xb = posb.back();
                    posa.pop_back(); posb.pop_back();
                    swap(ans[xa], ans[xb]);
                }
                if(!flag){
                    printf("-1\n");
                    continue;
                }
            }
        }
        for(int i = 1; i <= 2 * n; i++) printf("%c",ans[i]);
        printf("\n");
    }
    return 0;
}
```
## PART 4：后记 & 花絮
总有人会问，为什么入门赛你要写这么长的代码。~~（你以为我想吗？）~~

那原因就只是作者太弱而想不到列两个式子直接求解。

然后，考试的时候，B 题调了本人将近 1h，D 一开始在写各种复杂的写法，E 也差 1min 没交赢，直接挂调。

同机房的 L 君比我晚来 1h，他来的时候我还在打第二题，然后我们几乎是同时过掉 5 个题目的，他问我那些没过，我说最后两题和 E 题，他说他最后三题没有打，我说 E 题代码好长，还有二十多分钟就估计没时间打了，不如看看后面两题，结果他不到五十行就写完了，他 A 掉的时候本人还在调 E 题的模拟，结果考后发现是因为中间变量没有开 `unsigned long long`。然后他又比我高 100 多名。前面有几题不是没有考虑完整就是每开 `long long` 多了几次罚时。

十年 OI 一场空，不开 `long long` 见祖宗。

十年 OI 一场空，不测样例见祖宗

十年 OI 一场空，不写对拍见祖宗

$Update:2022/8/8/17:53$ 应 L 君强烈要求，在此把他 @ 出来，大家快去膜他：@[Wilson_Lee](https://www.luogu.com.cn/user/513900)

---

## 作者：tiger2008 (赞：5)

# P8471 琪露诺的选择题 题解

[传送门](https://www.luogu.com.cn/problem/P8471)

### 思路及分析

假如有在一个 $2 \times n$ 的字符串里有 $x$ 个字母 "$A$" ，我们会发现我们每次将一个 "$A$" 修改成一个 "$B$" 时，$x$ 的数量 $ - 1$ ；而我们每次将一个 "$B$" 修改成一个 "$A$" 时，$x$ 的数量 $ + 1$ 。

意味着如果你想让最后有 $e$ 个与原字符串不同的话，你必须要保证 $+ 1$ 的个数和 $- 1$ 的个数的差为 $e - x$ ，那么就可以根据这个思路来写代码了。

特判一下输出 "$-1$" 的情况就可以了。

### Code:

下面是蒟蒻的代码，不太好看：

```cpp
#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;
int n;
int main(){
	cin>>n;
	while(n--){
		int a,b,c;
		cin>>a>>b>>c;
		string s;
		cin>>s;
		int tmp=0;
		for(int i=0;i<s.length();i++)
			if(s[i]=='A')
				tmp++;//求出A的个数 
		if(abs(tmp-b)%2!=c%2)//如果要改变个数和你能操作个数的奇偶性不同就不可以 
			cout<<"-1"<<"\n";
		else{
			int tmp_A=(c-abs(tmp-b))/2;//将A变成B的个数 
			int tmp_B=tmp_A;//将B变成A的个数 
			int tmp1=0; 
			int tmp_1=tmp-b;
			for(int i=0;i<s.length();i++){//我用了最易懂的方法，直接从前面暴力修改 
				if(s[i]=='A' && tmp_A>0){
					s[i]='B';
					tmp_A--;
				}else if(s[i]=='B' && tmp_B>0){
					s[i]='A';
					tmp_B--;
				}else if(tmp_1>0 && s[i]=='A'){
					s[i]='B';
					tmp_1--;
				}else if(tmp_1<0 && s[i]=='B'){
					s[i]='A';
					tmp_1++;
				}
				if(!tmp_A && !tmp_B && !tmp_1)//如果都为0就可直接break 
					break;
			}
			if(tmp_1!=0 || tmp_A!=0 || tmp_B!=0)//如果其中一个没有完成，意味着不成立，输出-1 
				cout<<"-1"<<"\n";
			else
				cout<<s<<"\n";//把原字符串输出 
		}
	} 
	return 0;
}
```


### 总结：

一道比较简单的套路题。
 

---

## 作者：DesignDigits (赞：1)

> ## 题意简述
>
> 给定一个字符 $\texttt{A, B}$ 构成的字符串，求一个与它等长的字符串，也由 $\texttt{A, B}$ 构成，且包含 $a$ 个 $\texttt A$，和原串有 $e$ 处不同。

## 解法

与其求一个新串，我们不如考虑在原串上进行 $e$ 次 **修改**，每次改一个字符。

对修改后的串的要求，只有 “要有 $a$ 个 $\texttt A$” 一条，这就告诉我们，只需关注 $\texttt A$ 与 $\texttt B$ 的 **数量，而它们的位置则是任意的**。这也是本题有多解的原因。

那么，我们要求出新串 **之一**，就只需知道，要把多少个 $\texttt A$ 改为 $\texttt B$，以及要把多少个 $\texttt B$ 改为 $\texttt A$。我们把这两个数量设为 $x$ 和 $y$。

如何求 $x$ 和 $y$ 呢？到题目中找条件。

- **所求串的长度为 $2n$。** 无论修改多少次，串的长度都是 $2n$，故无法列出关于 $x, y$ 的方程。

- **所求串由 $\texttt{A, B}$ 构成。** 同样，无论无论修改多少次都能满足这个条件，也无法列出方程。

- **所求串包含 $a$ 个 $\texttt A$。** 有用的来了！原串中 $\texttt A$ 的数量 $a'$ 只要遍历一遍原串即可求，或者我们 ~~偷个小懒~~ 用 `a_ =  count(s.begin(), s.end(), 'A')` 也行（`count` 函数在 `algorithm` 头文件里）。而一次 $\texttt A$ 改为 $\texttt B$ 会少一个 $\texttt A$，一次 $\texttt B$ 改为 $\texttt A$ 会多一个 $\texttt A$，故有：

$$ a'+x\cdot(-1)+y\cdot 1=a$$
$$ -x+y=a-a'\ (1) $$

- **所求串和原串有 $e$ 处不同。** 由于两种修改都会造成一处不同，故

$$ x+y=e\ (2) $$

OK，条件看完了，我们发现，两个未知数，两个方程，可以解出来！

$$\frac{(1)+(2)} 2: y=\frac{a-a'+e} 2$$
$$\frac{-(1)+(2)} 2: x=\frac{-a+a'+e} 2$$

**这时必须保证：** 我们的 $x$ 是 $0\sim a'$ 的整数，$y$ 是 $0\sim b'$ 的整数。（不然你就没法修改了对不对）如果不符合，输出 `-1`。
 
> 如何判整数？可以看分子，如果 `(-a+a_+e)&1==1` ，$x$ 即为整数。而且只需判一次，因为两个数和为整数，所以只要 $x$ 是整数，$y$ 肯定也是。

那最后就很简单了：把原串里的前 $x$ 个 $\texttt A$ 换成 $\texttt B$，把原串里的前 $y$ 个 $\texttt B$ 换成 $\texttt A$ ——此处注意，必须一个循环里同时做这两件事；如果你先一次全部 $\texttt A \to \texttt B$ 后，再 $\texttt B$ 换成 $\texttt A$，就会把你刚刚变出来的 $\texttt B$ 又变回去了。这个时候本来的 $2$ 次更改就会变成 $0$ 次，不符合题意。

最后输出得到的串即可。

> PS: 感觉这个可以评橙的，你看这年头 KMP 都才黄（

```
int a_ = count(s.begin(), s.end(), 'A'), b_ = count(s.begin(), s.end(), 'B');
if((a-a_+e)&1) {cout<<"-1\n"; continue; }
int x=-a+a_+e>>1, y=a-a_+e>>1;
if(x<0 || x>a_ || y<0 || y>b_) cout<<"-1\n";
else{
	int A_edited=0, B_edited=0;
	for(int i=0; i<2*n; i++){
		if(s[i]=='A' && A_edited<x){
			s[i]='B';
			A_edited++;
		}
		else if(s[i]=='B' && B_edited<y){
			s[i]='A';
			B_edited++;
		}
	}
	cout<<s<<"\n";
}

---

## 作者：eastcloud (赞：0)

## P8471 琪露诺的选择题 题解

### 题目分析

观察到到错的题目交换对答案没有影响，并且可以无限次更改，我们先考虑要更改的 A，B 的数量。

首先满足 A 的数量为 $ a $ 的条件，计算当前数量，多则增加 A ，反之则增加 B。

其次，对于剩下来要满足的错题数，设为 $ s $，可以采取对原本正确的 A 和 B （设为 $ x $ 与 $ y $）各更改一次的操作，两字符更改的数量各增加 $ \frac{s}{2} $ 即可

对于所有无解的情况，有以下几种可能：

1.  $ s < 0 $ 

2.  $ s \equiv1\pmod2 $

3.  $ \frac{s}{2} > \min(x,y) $

最后根据需要修改的数量输出即可。

### 代码

```
#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cmath>
using namespace std;
int num[10000001];
int main(){
	int t,n,a,e;
	char ch;
	cin>>t;
	while(t--){
		cin>>n>>a>>e;
		int sum=0,wa=0,wb=0;
		for(int i=1;i<=2*n;i++){
			cin>>ch;
			if(ch=='B') num[i]=1;
			else sum++;
		}
		if(a>sum) wb+=(a-sum);
		else wa+=(sum-a);
		e-=(wa+wb);
		if(e<0 || (e%2==1 || min(sum-wa,(2*n-sum)-wb)<e/2)){
			cout<<-1<<endl;
			for(int i=1;i<=2*n;i++)num[i]=0;
			continue;
		}
		wa+=e/2;
		wb+=e/2;
		for(int i=1;i<=2*n;i++){
			if(num[i]==0 && wa){
				wa--;
				cout<<'B';
			}
			else if(num[i]==0) cout<<'A';
			else if(num[i]==1 && wb){
				wb--;
				cout<<'A';
			}
			else cout<<'B';
		}
		cout<<endl;
		for(int i=1;i<=2*n;i++)num[i]=0;
	}
}
```


---

## 作者：封禁用户 (赞：0)

## 题意简述

有 $T$ 组测试数据。

对于每一组测试数据，有 3 个整数 $n$，$a$，$e$ 和一个字符串 $s$，其中 $s$ 的长度为 $2 \times n$，且仅包含 A B 两种字符。

你需要构造出一个字符串 $t$，使得恰好有 $a$ 个 A 在 $s$ 中，且 $(\sum\limits_{i=1}^{2n} [s_i \neq t_i])=e$。

对于 $[a]$ ，如果 $a$ 为真则表达式为 1 ， 否则为 0 。

## 题目分析

一道构造题。

我们扫一遍 $s$，直到已经有足够多的错误。如果当前字符是 A，那么如果当前 A 的数量已经足够就把 A 替换成 B。B 同理，如果当前 A 的数量不足就把 B 换成 A 。

这里有一个特殊情况：如果 A 的数量刚刚好且错误还不够多，那么我们就把 A 换成 B，B 换成 A。

于是这道构造题就被我们水完了，具体细节看代码。

## AC Code

```cpp
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

void run() {
	int n, a, e;
	cin >> n >> a >> e;
	string s, t;
	cin >> s;
	t = s;
	int cnt = count(s.begin(), s.end(), 'A') - a;  // 还能换多少次A到B 
	for (int i = 0; i < n + n && e; i++) {
		if (cnt == 0) {  // A的数量正好 
			e--;
			// A换B，B换A 
			if (s[i] == 'A') {
				cnt--;
				t[i] = 'B';
			} else {
				cnt++;
				t[i] = 'A';
			}
		}
		if (s[i] == 'A') {
			if (cnt > 0) {  // 如果当前A的数量够多了，那么就换一个A出去 
				cnt--;
				e--;
				t[i] = 'B';
			}
		} else {
			if (cnt < 0) {  // 如果当前A的数量不够多，那么就换一个B变成A 
				cnt++;
				e--;
				t[i] = 'A';
			}
		}
	}
	if (cnt || e) cout << -1 << endl;  // 如果最后A的数量不符合要求或者不能满足e个错误，输出-1 
	else cout << t << endl;
}

int main() {
	int t;
	cin >> t;
	while (t--) run();
	return 0;
}
```

## 时间复杂度

我们发现一共会进行 $2 \times n$ 次循环，循环内时间复杂度为 $O(1)$，所以整体时间复杂度为 $O(n)$，可以通过本题。

---

