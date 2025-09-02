# コンテスト

## 题目描述

[problemUrl]: https://atcoder.jp/contests/tdpc/tasks/tdpc_contest

入力は以下の形式で標準入力から与えられる。

> $ N $ $ p_1\ p_2\ ...\ p_N $

 答えを一行に出力せよ。 ```

3
2 3 5
```

```

7
```

```

10
1 1 1 1 1 1 1 1 1 1
```

```

11
```

## 说明/提示

### Constraints

 $ N $ 問の問題があるコンテストがあり、$ i $ 問目の問題の配点は $ p_i $ 点である。コンテスタントは、この問題の中から何問か解き、解いた問題の配点の合計が得点となる。このコンテストの得点は何通り考えられるか。

- - - - - -

- $ 1\ <\ =\ N\ <\ =\ 100 $
- $ 1\ <\ =\ p_i\ <\ =\ 100 $

# 题解

## 作者：RioBlu (赞：4)

使用暴力即可

暴力思路：0分肯定是能拿的，对于一个新来的分数：b

假设之前$f[x]==ture$即f[x]可以拿到，那么f[x+b]也可以拿到

### 代码如下
```
#include<bits/stdc++.h>
using namespace std;
long long a,b,ans;
bool c[10005];
int main()
{
    cin>>a;
    c[0]=1;
    for(int s=0;s<a;s++)
    {
        cin>>b;
        for(int v=10002;v>=0;v--)
        {
            if(c[v]==1)
            {
                c[v+b]=1;
            }
        }
    }
    for(int s=0;s<10002;s++)
    {
        if(c[s]==1)ans++;
    }
    cout<<ans<<endl;
}
```

---

