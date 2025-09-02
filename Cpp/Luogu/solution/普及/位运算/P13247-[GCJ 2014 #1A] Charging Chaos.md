# [GCJ 2014 #1A] Charging Chaos

## 题目描述

农夫 Shota 遇到了一点麻烦。他刚刚搬进自己新建的农舍，却发现房子的插座无法正确为他所有的设备充电。作为一位现代农夫，Shota 拥有大量的智能手机和笔记本电脑，甚至还为他最喜爱的奶牛 Wagyu 准备了一台平板电脑。总共，他拥有 $N$ 个不同的设备。

由于这些设备由不同厂商制造，规格也各不相同，因此每个设备都需要不同的电流格式来进行充电。同样地，房子中的每个插座也输出特定格式的电流。一个电流格式可以用一个长度为 $L$ 的仅包含 $0$ 和 $1$ 的字符串来表示。

Shota 希望能够同时为他所有的 $N$ 个设备充电。恰好，他新家的插座数量也正好是 $N$ 个。为了配置插座的电流格式，房子里设有一个总控制面板，带有 $L$ 个开关。第 $i$ 个开关用于**翻转每个插座输出电流格式中的第 $i$ 位**。例如，如果初始插座的电流格式如下：

```
插座 0：10
插座 1：01
插座 2：11
```

那么翻转第 2 个开关之后，插座的电流格式将变为：

```
插座 0：11
插座 1：00
插座 2：10
```

如果 Shota 的智能手机需要电流格式 `"11"` 充电，平板电脑需要 `"10"`，笔记本电脑需要 `"00"`，那么只需翻转第二个开关，他就可以非常开心地同时为所有设备充电了！

为了解决这个问题，Shota 雇佣了 Misaki 来帮忙。Misaki 测量了所有插座的电流格式，并发现它们都是不同的。现在你的任务是判断 Shota 是否可能通过翻转一些开关来让所有设备都能充电。如果可能，请计算出**所需翻转的最少开关数**，因为这些开关又大又重，Misaki 不想做无用功。


## 说明/提示

**样例说明**

在第一个测试用例中，Misaki 只需翻转第二个开关一次，插座电流格式变为：

```
插座 0：00
插座 1：10
插座 2：11
```

此时 Shota 可以使用插座 0 给设备 1 充电，插座 1 给设备 2 充电，插座 2 给设备 0 充电。这是所需翻转开关次数最少的一个解决方案。

## 限制条件

- $1 \leq T \leq 100$
- 初始状态下，任意两个插座的电流格式都不同
- 任意两个设备所需的电流格式也都不同

**小数据集**

- 时间限制：~~60~~ 3 秒
- $1 \leq N \leq 10$
- $2 \leq L \leq 10$

**大数据集**

- 时间限制：~~120~~ 5 秒
- $1 \leq N \leq 150$
- $10 \leq L \leq 40$

翻译由 ChatGPT-4o 完成。

## 样例 #1

### 输入

```
3
3 2
01 11 10
11 00 10
2 3
101 111
010 001
2 2
01 10
10 01```

### 输出

```
Case #1: 1
Case #2: NOT POSSIBLE
Case #3: 0```

# 题解

## 作者：fish_love_cat (赞：5)

**简要题意：**

给定集合 $a,b$，寻找 $\text{popcount}$ 最小的 $k$ 使得 $a$ 中的每一个数异或上 $k$ 后可以得到 $a'=b$。

若不存在报告无解。

---

由于 $a'$ 中每一个数字都可以在 $b$ 中找到，所以我们将每一个 $b$ 中的数字与 $a$ 的某一个固定元素异或得到一个可能的 $k$ 后，模拟进行 check 并取最优即可。

时间复杂度 $O(Tn^2)$，跑得飞快。

```cpp
#include<bits/stdc++.h>
#define int long long
using namespace std;
int a[155],b[155],c[155];
int flc;
void solve(){
    printf("Case #%d: ",++flc);
    int n,m;
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        string s;
        cin>>s;
        a[i]=0;
        for(int j=0;j<m;j++)
        a[i]+=(1ll<<(m-j-1))*(s[j]-'0');
    }
    for(int i=1;i<=n;i++){
        string s;
        cin>>s;
        b[i]=0;
        for(int j=0;j<m;j++)
        b[i]+=(1ll<<(m-j-1))*(s[j]-'0');
        c[i]=b[i];
    }
    sort(a+1,a+1+n);
    int ans=1e9;
    for(int i=1;i<=n;i++){
        int k=c[i]^a[1];
        for(int j=1;j<=n;j++)
        b[j]^=k;
        sort(b+1,b+1+n);
        bool flc=1;
        for(int j=1;j<=n;j++){
            if(b[j]!=a[j])flc=0;
            b[j]^=k;
        }
        if(flc){
            int ret=0;
            while(k){
                ret+=k&1;
                k>>=1;
            }
            ans=min(ret,ans);
        }
    }
    if(ans==1e9)puts("NOT POSSIBLE");
    else cout<<ans<<'\n';
}
signed main(){
    int t;
    cin>>t;
    while(t--)solve();
    return 0;
}
// 直到公园的风吹起羽毛
// 才想起还有飞翔细胞
```

---

## 作者：IkillDream (赞：1)

# P13247 题解

## 思路

我们只需要枚举对每个设备 $D$，计算与第一个插座 $O$ 的异或掩码 $X=D \operatorname{xor} O$，接着用 $X$ 异或所有插座，检查结果是否匹配设备集合，然后记录所有可行掩码中 $1$ 的个数最小值，最后如果存在解则输出最小次数，否则输出 ```NOT POSSIBLE```。

## [AC points](https://www.luogu.com.cn/record/225292722) 代码

```c++
#include<bits/stdc++.h>
using namespace std;
int main(){
    int t;
    cin>>t;
    for(int kkk01=1;kkk01<=t;kkk01++){
        int n,l;
        cin>>n>>l;
        string o[155],d[155];
        for(int i=0;i<n;i++)cin>>o[i];
        for(int i=0;i<n;i++)cin>>d[i];
        sort(d,d+n);
        int ans=l+1;
        for(int i=0;i<n;i++){
            string p(l,'0');
            for(int j=0;j<l;j++)
                if(o[0][j]!=d[i][j])p[j]='1';
            string f[155];
            for(int k=0;k<n;k++){
                f[k]=o[k];
                for(int j=0;j<l;j++)
                    if(p[j]=='1')f[k][j]=(f[k][j]=='0')?'1':'0';
            }
            sort(f,f+n);
            bool ok=1;
            for(int k=0;k<n;k++)
                if(f[k]!=d[k]){ok=0;break;}
            if(ok){
                int cnt=0;
                for(int j=0;j<l;j++)
                    if(p[j]=='1')cnt++;
                if(cnt<ans)ans=cnt;
            }
        }
        if(ans<=l)cout<<"Case #"<<kkk01<<": "<<ans<<endl;
        else cout<<"Case #"<<kkk01<<": NOT POSSIBLE"<<endl;
    }
    return 0;
}
```

## 后记

题解制作不容易如果觉得我的题解写的好的话可以点个赞吗 qwq。

题解可以抄，但是你要学会哦！

祝大家 CSP-J/S 初赛，会的都对，蒙的全对。

---

## 作者：nice_hamburger (赞：0)

# Charging Chaos 题解

## 题目大意

共 $T$ 组询问，对于每组询问，给定一个初始数组和一个目标数组，询问能否通过若干次对全部初始数组某位异或得到目标数组，并输出最小次数。以下称给定的字符串数组为 $model$，期望的字符串数组为 $need$。

## 思路

还是有点难度的。

先从简单情况考虑，假设某一列上有 $k$ 个 $1$，那么取反之后就会变成 $n-k$ 个 $1$，所以可以先写一个特判，如果不论怎么取反都达不到预期，那就直接输出无解。

接着考虑复杂一点的情况，首先注意到一点：任何可行的方案中，必须至少有一个插座必须匹配某个设备，这也就意味着我们可以随便拿一个 $need$ 串作为参照，这样就可以在枚举方面将 $O(n^2)$ 的复杂度降到 $O(n)$，这里我拿第一个作为参照，方便一点。

接着注意到一个细节，我们肯定是要对数组排序的（方便我们在后面比较），但是直接排序的时间复杂度是 $O(n \log n\times L)$，因为字符串的比较是逐位比较的，这明显太大了，所以考虑把字符串转为整型，但是 $L$ 最大有 $40$，$32$ 位整型无法完全储存，所以我们用 $64$ 位整型储存。

然后，我们要在循环中处理需要取反的位置，压入二进制中，类似状压，没基础的可以看看[这个](https://oi-wiki.org/math/bit/)，应该有点帮助。处理完位置问题后，剩下的就很简单了，由于异或的优良性质，我们可以在 $O(1)$ 复杂度内实现翻转，我们只需要对于每一个 $model$ 串与我们得到的掩码 $mask$ 异或就能得到翻转的结果就行了，最后再对操作后的数组排序，与 $need$ 数组逐位比较即可，注意一下转换时的对应位置即可。

#### Tips

计算一个数的二进制的一的个数可以手写函数，也可以考虑用内置函数，时间复杂度为 $O(1)$，代码注释中有提到。

### [AC](https://www.luogu.com.cn/record/225956748)code

```cpp
#include<bits/stdc++.h>
#define int long long

using namespace std;
const int N = 160;

inline int read(){
    int f = 1, k = 0;
    char c = getchar();
    while(!isdigit(c)){
        if(c == '-') f = -1;
        c = getchar();
    }
    while(isdigit(c)){
        k = k * 10 + c - '0';
        c = getchar();
    }
    return f * k;
}

int T, n, L, cnt;
string model[N], need[N];
int a[45], b[45];

void err(){//无解
    cout << "Case #" << ++cnt << ": NOT POSSIBLE\n";
}
void print(int ans){//有解
    cout << "Case #" << ++cnt << ": " << ans << '\n';
}
int turn(string s){//字符串转整型
    int ans = 0;
    for(int i = 0;i < L;i++){
        ans = (ans << 1) | (s[i] - '0');
    }
    return ans;
}
signed main(){
    T = read();
    while(T--){
        n = read(),L = read();
        int ans = 1e8;
        memset(a,0,sizeof a);
        memset(b,0,sizeof b);
        for(int i = 1;i <= n;i++) cin >> model[i];
        for(int i = 1;i <= n;i++) cin >> need[i];
        for(int i = 1;i <= n;i++){
            for(int j = 0;j < L;j++){
                if(model[i][j] == '1') a[j + 1]++;
                if(need[i][j] == '1') b[j + 1]++;
            }
        }
        bool f = 1;
        for(int i = 1;i <= L;i++){
            if(a[i] != b[i] && n - a[i] != b[i]){
                f = 0;
                err();
                break;
            }
        }
        if(!f) continue;//特判
        sort(need + 1,need + 1 + n);
        int need_int[N];
        for(int i = 1; i <= n; i++) {
            need_int[i] = turn(need[i]);
        }
        sort(need_int + 1, need_int + 1 + n);
        int model_int[N];
        for(int i = 1; i <= n; i++) {
            model_int[i] = turn(model[i]);
        }
        for(int i = 1; i <= n; i++) {
            int mask = 0;//掩码
            for(int j = 0;j < L;j++) {
                if(model[i][j] != need[1][j]) {
                    mask |= (1ll << j);
                }
            }
            int mask_int = 0;
            for(int j = 0;j < L;j++) {
                if(mask & (1ll << j)) {
                    mask_int |= (1ll << (L - 1 - j));
                }
            }
            int p_int[N];
            for(int j = 1;j <= n;j++) {
                p_int[j] = model_int[j] ^ mask_int;
            }
            sort(p_int + 1, p_int + 1 + n);
            bool fl = 0;
            for(int j = 1; j <= n; j++) {
                if(p_int[j] != need_int[j]) {
                    fl = 1;
                    break;
                }
            }
            if(!fl) {
                int cnt_bits = __builtin_popcountll(mask);//内置函数
                ans = min(ans, cnt_bits);
            }
        }
        if(ans == 1e8) err();
        else print(ans);
    }
    return 0;
}
```

---

