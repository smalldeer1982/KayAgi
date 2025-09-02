# 题目信息

# Fence Painting

## 题目描述

You finally woke up after this crazy dream and decided to walk around to clear your head. Outside you saw your house's fence — so plain and boring, that you'd like to repaint it.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1481C/31e7d7ee4094f34ab2e6d6908f5b67e5f8eebe96.png)You have a fence consisting of $ n $ planks, where the $ i $ -th plank has the color $ a_i $ . You want to repaint the fence in such a way that the $ i $ -th plank has the color $ b_i $ .

You've invited $ m $ painters for this purpose. The $ j $ -th painter will arrive at the moment $ j $ and will recolor exactly one plank to color $ c_j $ . For each painter you can choose which plank to recolor, but you can't turn them down, i. e. each painter has to color exactly one plank.

Can you get the coloring $ b $ you want? If it's possible, print for each painter which plank he must paint.

## 样例 #1

### 输入

```
6
1 1
1
1
1
5 2
1 2 2 1 1
1 2 2 1 1
1 2
3 3
2 2 2
2 2 2
2 3 2
10 5
7 3 2 1 7 9 4 2 7 9
9 9 2 1 4 9 4 2 3 9
9 9 7 4 3
5 2
1 2 2 1 1
1 2 2 1 1
3 3
6 4
3 4 2 4 1 2
2 3 1 3 1 1
2 2 3 4```

### 输出

```
YES
1
YES
2 2
YES
1 1 1
YES
2 1 9 5 9
NO
NO```

# AI分析结果

### 题目内容（中文重写）
# 栅栏粉刷

## 题目描述
你在这个疯狂的梦境后终于醒来，决定四处走走清醒一下头脑。在外面，你看到了自家的栅栏——如此平淡无奇，你想要重新粉刷它。

![图片](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1481C/31e7d7ee4094f34ab2e6d6908f5b67e5f8eebe96.png)
你有一个由 $n$ 块木板组成的栅栏，其中第 $i$ 块木板的颜色为 $a_i$。你想将栅栏重新粉刷成第 $i$ 块木板颜色为 $b_i$ 的样子。

你邀请了 $m$ 位油漆工来完成这项工作。第 $j$ 位油漆工将在时刻 $j$ 到达，并将恰好一块木板重新粉刷成颜色 $c_j$。对于每位油漆工，你可以选择要重新粉刷的木板，但你不能拒绝他们，即每位油漆工必须恰好粉刷一块木板。

你能得到你想要的颜色 $b$ 吗？如果可以，请为每位油漆工打印出他必须粉刷的木板编号。

## 样例 #1

### 输入
```
6
1 1
1
1
1
5 2
1 2 2 1 1
1 2 2 1 1
1 2
3 3
2 2 2
2 2 2
2 3 2
10 5
7 3 2 1 7 9 4 2 7 9
9 9 2 1 4 9 4 2 3 9
9 9 7 4 3
5 2
1 2 2 1 1
1 2 2 1 1
3 3
6 4
3 4 2 4 1 2
2 3 1 3 1 1
2 2 3 4
```

### 输出
```
YES
1
YES
2 2
YES
1 1 1
YES
2 1 9 5 9
NO
NO
```

### 算法分类
模拟

### 综合分析与结论
这些题解的核心思路都是倒序处理油漆工的粉刷操作，因为后面的粉刷会覆盖前面的，所以倒序能更好地处理颜色覆盖问题。在处理每个油漆工时，会根据不同情况进行选择，如优先粉刷需要改变颜色且目标颜色匹配的木板，若没有则考虑刷在已粉刷或同色的木板上，若都不满足则无解。

各题解的算法要点主要包括使用 `vector` 或 `stack` 存储不同颜色木板的位置，以及使用数组记录相关信息。解决的难点在于对各种情况的分类讨论和边界条件的处理，如没有可刷木板、颜色不匹配等情况。

### 所选题解
- **作者：chlchl（4星）**
    - **关键亮点**：思路清晰，对涂色方法和情况分析明确，代码实现简洁易懂。
    - **个人心得**：思维难度不高，主要是代码实现和分类讨论，通过本题能提升码力和逻辑思维。
- **作者：xuezhe（4星）**
    - **关键亮点**：代码简洁，逻辑清晰，对倒序操作的处理直接明了。
- **作者：Theophania（4星）**
    - **关键亮点**：详细说明了工人粉刷的两种选择，代码实现规范，对各种情况的处理合理。

### 重点代码
#### chlchl 的代码
```cpp
#include<bits/stdc++.h>
using namespace std;

const int N = 1e5 + 10;
int T, n, m, ans[N], a[N], b[N], c[N], col[N];
vector<int> g[N];

void solve(){
    scanf("%d%d", &n, &m);
    for(int i=1;i<=n;i++)
        g[i].clear(), col[i] = -1;
    for(int i=1;i<=n;i++)
        scanf("%d", &a[i]);
    for(int i=1;i<=n;i++){
        scanf("%d", &b[i]);
        if(a[i] != b[i])
            g[b[i]].push_back(i);
        else if(a[i] == b[i])
            col[a[i]] = i;
    }
    for(int i=1;i<=m;i++)
        scanf("%d", &c[i]);
    int lst = -1;
    for(int i=m;i>=1;i--){
        if(g[c[i]].size() > 0)
            lst = ans[i] = g[c[i]].back(), g[c[i]].pop_back();
        else if(lst != -1)
            ans[i] = lst;
        else if(col[c[i]] != -1)
            ans[i] = lst = col[c[i]];
        else
            return printf("NO\n", i), void(0);
    }
    for(int i=1;i<=n;i++)
        if(g[i].size() > 0)
            return printf("NO\n"), void(0);
    printf("YES\n");
    for(int i=1;i<=m;i++)
        printf("%d ", ans[i]);
    printf("\n");
    return ;
}

int main(){
    scanf("%d", &T);
    while(T--)
        solve();
    return 0;
}
```
**核心实现思想**：使用 `vector` 存储需要改变颜色的木板位置，使用数组记录同色木板位置。倒序遍历油漆工，根据不同情况选择粉刷的木板，最后检查是否还有需要改变颜色的木板。

#### xuezhe 的代码
```cpp
int T,n,m,a[100005],b[100005],c[100005],d[100005],o[100005];
vector<int> f[100005];
int main(){
    cin>>T;
    while(T--){
        cin>>n>>m;
        for(int i=1;i<=n;++i)
            cin>>a[i];
        for(int i=1;i<=n;++i)
            cin>>b[i];
        for(int i=1;i<=m;++i)
            cin>>c[i];
        for(int i=1;i<=n;++i)
            d[i]=0,f[i].clear();
        for(int i=1;i<=n;++i){
            d[b[i]]=i;
            if(a[i]!=b[i])
                f[b[i]].push_back(i);
        }
        bool flg=true;
        for(int i=m;i;--i){
            if(f[c[i]].size()){
                o[i]=f[c[i]].back();
                f[c[i]].pop_back();
            }else if(d[c[i]]){
                o[i]=d[c[i]];
            }else if(i!=m){
                o[i]=o[m];
            }else{
                flg=false;
                break;
            }
        }
        if(flg)
            for(int i=1;i<=n;++i)
                if(f[i].size())
                    flg=false;
        if(flg){
            puts("YES");
            for(int i=1;i<=m;++i)
                printf("%d ",o[i]);
            putchar(10);
        }else{
            puts("NO");
        }
    }
    return 0;
}
```
**核心实现思想**：使用 `vector` 存储需要改变颜色的木板位置，使用数组记录同色木板位置。倒序遍历油漆工，根据不同情况选择粉刷的木板，最后检查是否还有需要改变颜色的木板。

#### Theophania 的代码
```cpp
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<ll> vll;
template <typename T>
inline void read(T &x)
{
    T data = 0, f = 1;
    char ch = getchar();
    while (!isdigit(ch))
    {
        if (ch == '-')
            f = -1;
        ch = getchar();
    }
    while (isdigit(ch))
    {
        data = (data << 3) + (data << 1) + ch - '0';
        ch = getchar();
    }
    x = f * data;
}
template <typename T, typename... Args>
inline void read(T &t, Args &...args)
{
    read(t);
    read(args...);
}
const int maxn = 1e5 + 9;

vi p[maxn];
int a[maxn], b[maxn], c[maxn], color[maxn], ans[maxn];
signed main()
{
    int T;
    read(T);
    while (T--)
    {
        int n, m, done = 0;
        bool flag = true;
        read(n, m);
        for (int i = 1; i <= n; ++i)
            read(a[i]);
        for (int i = 1; i <= n; ++i)
        {
            read(b[i]);
            if (a[i] != b[i])
                p[b[i]].push_back(i); // 标记需要粉刷的位置
            else
                color[b[i]] = i; // 标记第一种选择的位置
        }
        for (int i = 1; i <= m; ++i)
            read(c[i]);
        for (int i = m; i; --i)
        {
            if (!p[c[i]].empty())
            {
                ans[i] = p[c[i]].back();
                p[c[i]].pop_back();
                if (!done)
                    done = ans[i]; // 可以让前面的人刷在这里
            }
            else if (done) // 第二种选择
                ans[i] = done;
            else if (color[c[i]]) // 第一种选择
            {
                ans[i] = color[c[i]];
                done = ans[i];
            }
            else
            {
                flag = false;
                break;
            }
        }
        for (int i = 1; i <= n; ++i)
            if (!p[i].empty())
            {
                flag = false;
                break;
            }
        if (flag)
        {
            cout << "YES\n";
            for (int i = 1; i <= m; ++i)
                cout << ans[i] << ' ';
            cout << '\n';
        }
        else
            cout << "NO\n";
        for (int i = 1; i <= n; ++i)
        {
            p[i].clear();
            color[i] = 0;
        }
    }
    return 0;
}
```
**核心实现思想**：使用 `vector` 存储需要改变颜色的木板位置，使用数组记录同色木板位置。倒序遍历油漆工，根据不同情况选择粉刷的木板，最后检查是否还有需要改变颜色的木板。

### 最优关键思路或技巧
- 倒序处理油漆工的粉刷操作，利用颜色覆盖的特性简化问题。
- 使用 `vector` 或 `stack` 存储不同颜色木板的位置，方便查找和操作。
- 对各种情况进行分类讨论，确保每种情况都能正确处理。

### 拓展思路
同类型题可能会有更多的限制条件或更复杂的场景，如油漆工有不同的工作效率、木板有不同的属性等。类似算法套路主要是模拟类问题，需要根据具体情况进行分类讨论和模拟操作。

### 推荐题目
- [P1042 乒乓球](https://www.luogu.com.cn/problem/P1042)
- [P1067 多项式输出](https://www.luogu.com.cn/problem/P1067)
- [P1098 字符串的展开](https://www.luogu.com.cn/problem/P1098)

### 个人心得摘录与总结
- **龙潜月十五**：这是一道模拟题，因细节多 WA 了好几发，提醒多组数据一定要清空数组。
- **chlchl**：思维难度不高，主要是代码实现和分类讨论，通过本题能提升码力和逻辑思维。
- **huayucaiji**：本题细节较多，通过时只有 600 人左右通过，要注意数组清空。 

---
处理用时：84.37秒