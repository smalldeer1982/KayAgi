# 順列辞書

## 题目描述

[problemUrl]: https://atcoder.jp/contests/code-festival-2016-qualc/tasks/codefestival_2016_qualC_e

ある日高橋君は、$ 1 $~$ N $ からなる $ N! $ 個の順列全てが載っている辞書を拾いました。辞書は $ N! $ ページからなり、 $ i\ (1≦i≦N!) $ ページ目には辞書順 $ i $ 番目の順列が載っています。高橋君はこの辞書で長さ $ N $ のある順列を調べようとしましたが、順列の一部の数は忘れてしまいました。そのため、可能性のある順列全てをこの辞書で調べようとしています。高橋くんが調べる必要のあるページ番号の総和を $ 10^9+7 $ で割ったあまりを求めてください。

順列の情報は $ P_1 $,$ P_2 $,$ ... $,$ P_N $ で与えられます。$ P_i=0 $ の時は順列の $ i $ 番目の数を忘れてしまったことを、そうでない場合は順列の $ i $ 番目の数が $ P_i $ であることを意味します。

## 说明/提示

### 制約

- $ 1≦N≦500000 $
- $ 0≦P_i≦N $
- $ i≠j\ (1≦i,j≦N) $ かつ $ P_i≠0 $ かつ $ P_j≠0 $ ならば、 $ P_i≠P_j $

### 部分点

- $ 1≦N≦3000 $ を満たすデータセットに正解すると、$ 500 $ 点が与えられる。

### Sample Explanation 1

ありうる順列は$ [1,2,3,4] $と$ [4,2,3,1] $です。前者は$ 1 $ページ目に、後者は$ 22 $ページ目に載っているため、答えは$ 23 $です。

### Sample Explanation 2

長さ$ 3 $の全ての順列がありうるので、答えは$ 1+2+3+4+5+6\ =\ 21 $ になります。

### Sample Explanation 3

高橋君は完全に順列を記憶しています。

### Sample Explanation 4

辞書は$ 1 $ページからなります。

## 样例 #1

### 输入

```
4
0 2 3 0```

### 输出

```
23```

## 样例 #2

### 输入

```
3
0 0 0```

### 输出

```
21```

## 样例 #3

### 输入

```
5
1 2 3 5 4```

### 输出

```
2```

## 样例 #4

### 输入

```
1
0```

### 输出

```
1```

## 样例 #5

### 输入

```
10
0 3 0 0 1 0 4 0 0 0```

### 输出

```
953330050```

# 题解

## 作者：worldvanquisher (赞：4)

看到的时候感觉很典。实际上好像也很典？

看起来就很康托展开，那看看康托展开的式子：每个位置 $i$ 的贡献是 $i$ 开头的逆序对个数乘 $(n-i)!$ 最后 $+1$。那算个数。

四种情况：（设 $cnt_i$ 为 $<i$ 有几个数空着）

1. $i\to j$：需要 $a_i>a_j$，贡献 $cnt_n!$。
2. $i\to 0$：每个 $0$ 有贡献 $(cnt_n-1)!cnt_i$。
3. $0\to j$：每个 $j$ 贡献 $(cnt_n-1)!(cnt_n-cnt_j)$。
4. $0\to 0$：每个 $0$ 贡献 $\dfrac{cnt_n!}2$。

那只需要统计 $cnt_n-cnt_i$ 的后缀和和 $0$ 的后缀个数和，再树状数组算个逆序对。最后要加上 $cnt_n!$。
```cpp
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <queue>
#include <iostream>
using namespace std;
const int mod=1000000007,inv2=(mod+1)>>1;
int n,ans,a[500010],cnt[500010],jc[500010];
struct BIT{
    int c[500010];
    #define lowbit(x) (x&-x)
    void update(int x,int val){
        while(x<=n)c[x]+=val,x+=lowbit(x);
    }
    int query(int x){
        int sum=0;
        while(x)sum+=c[x],x-=lowbit(x);
        return sum;
    }
}c;
int main(){
    scanf("%d",&n);jc[0]=1;
    for(int i=1;i<=n;i++){
        scanf("%d",&a[i]);
        if(a[i])cnt[a[i]]--;
        jc[i]=1ll*jc[i-1]*i%mod;
    }
    for(int i=1;i<=n;i++)cnt[i]+=cnt[i-1]+1;
    int num=0,pre=0,suf=0;
    for(int i=n;i>=1;i--){
        if(a[i]==0){
            ans=(ans+1ll*jc[n-i]*inv2%mod*jc[cnt[n]]%mod*num)%mod;
            num++;
            ans=(ans+1ll*jc[n-i]*jc[cnt[n]-1]%mod*suf)%mod;
        }
        else{
            ans=(ans+1ll*jc[n-i]*jc[cnt[n]-1]%mod*cnt[a[i]]%mod*num)%mod;
            suf=(suf+cnt[n]-cnt[a[i]])%mod;
            ans=(ans+1ll*jc[n-i]*jc[cnt[n]]%mod*c.query(a[i]))%mod;
            c.update(a[i],1);
        }
    }
    ans=(ans+jc[cnt[n]])%mod;
    printf("%d\n",ans);
    return 0;
}
```

---

