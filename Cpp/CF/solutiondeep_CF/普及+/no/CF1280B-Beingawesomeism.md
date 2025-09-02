# 题目信息

# Beingawesomeism

## 题目描述

You are an all-powerful being and you have created a rectangular world. In fact, your world is so bland that it could be represented by a $ r \times c $ grid. Each cell on the grid represents a country. Each country has a dominant religion. There are only two religions in your world. One of the religions is called Beingawesomeism, who do good for the sake of being good. The other religion is called Pushingittoofarism, who do murders for the sake of being bad.

Oh, and you are actually not really all-powerful. You just have one power, which you can use infinitely many times! Your power involves missionary groups. When a missionary group of a certain country, say $ a $ , passes by another country $ b $ , they change the dominant religion of country $ b $ to the dominant religion of country $ a $ .

In particular, a single use of your power is this:

- You choose a horizontal $ 1 \times x $ subgrid or a vertical $ x \times 1 $ subgrid. That value of $ x $ is up to you;
- You choose a direction $ d $ . If you chose a horizontal subgrid, your choices will either be NORTH or SOUTH. If you choose a vertical subgrid, your choices will either be EAST or WEST;
- You choose the number $ s $ of steps;
- You command each country in the subgrid to send a missionary group that will travel $ s $ steps towards direction $ d $ . In each step, they will visit (and in effect convert the dominant religion of) all $ s $ countries they pass through, as detailed above.
- The parameters $ x $ , $ d $ , $ s $ must be chosen in such a way that any of the missionary groups won't leave the grid.

The following image illustrates one possible single usage of your power. Here, A represents a country with dominant religion Beingawesomeism and P represents a country with dominant religion Pushingittoofarism. Here, we've chosen a $ 1 \times 4 $ subgrid, the direction NORTH, and $ s = 2 $ steps.

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1280B/28f64f5dd2e3bc2e91270492183ebd3ec34bb40a.png)You are a being which believes in free will, for the most part. However, you just really want to stop receiving murders that are attributed to your name. Hence, you decide to use your powers and try to make Beingawesomeism the dominant religion in every country.

What is the minimum number of usages of your power needed to convert everyone to Beingawesomeism?

With god, nothing is impossible. But maybe you're not god? If it is impossible to make Beingawesomeism the dominant religion in all countries, you must also admit your mortality and say so.

## 说明/提示

In the first test case, it can be done in two usages, as follows:

Usage 1:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1280B/5aa9a3e986e676e61c160aa9ee967c57ee4ce5c6.png)Usage 2:

 ![](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1280B/100b5a5b446d54b176a5d3a43e9d6e720401be64.png)In the second test case, it can be done with just one usage of the power.

In the third test case, it is impossible to convert everyone to Beingawesomeism, so the answer is "MORTAL".

## 样例 #1

### 输入

```
4
7 8
AAPAAAAA
PPPPAAAA
PPPPAAAA
APAAPPPP
APAPPAPP
AAAAPPAP
AAAAPPAA
6 5
AAAAA
AAAAA
AAPAA
AAPAP
AAAPP
AAAPP
4 4
PPPP
PPPP
PPPP
PPPP
3 4
PPPP
PAAP
PPPP
```

### 输出

```
2
1
MORTAL
4
```

# AI分析结果

### 题目中文重写
# 至善主义

## 题目描述
你是一个无所不能的存在，并且你创造了一个矩形的世界。实际上，你的世界非常单调，以至于可以用一个 $r \times c$ 的网格来表示。网格上的每个单元格代表一个国家。每个国家都有一种占主导地位的宗教。在你的世界里只有两种宗教。其中一种宗教叫做“至善主义”（Beingawesomeism），他们为善而行善；另一种宗教叫做“极端主义”（Pushingittoofarism），他们为恶而作恶。

哦，实际上你并非真正的无所不能。你只有一种能力，而且可以无限次使用！你的能力与传教团体有关。当某个国家（设为 $a$）的传教团体经过另一个国家 $b$ 时，他们会将国家 $b$ 的主导宗教转变为国家 $a$ 的主导宗教。

具体来说，你使用一次能力的过程如下：
- 你选择一个水平的 $1 \times x$ 子网格或一个垂直的 $x \times 1$ 子网格。$x$ 的值由你决定；
- 你选择一个方向 $d$。如果你选择的是水平子网格，你的选择可以是“北”（NORTH）或“南”（SOUTH）；如果你选择的是垂直子网格，你的选择可以是“东”（EAST）或“西”（WEST）；
- 你选择步数 $s$；
- 你命令子网格中的每个国家派遣一个传教团体，该团体将朝着方向 $d$ 行进 $s$ 步。在每一步中，他们将访问（并因此改变主导宗教）他们经过的所有 $s$ 个国家，如上所述。
- 参数 $x$、$d$ 和 $s$ 的选择必须确保任何传教团体都不会离开网格。

下图展示了一次可能的能力使用情况。这里，`A` 代表以“至善主义”为主导宗教的国家，`P` 代表以“极端主义”为主导宗教的国家。在这里，我们选择了一个 $1 \times 4$ 的子网格，方向为“北”（NORTH），步数 $s = 2$。

![图片](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1280B/28f64f5dd2e3bc2e91270492183ebd3ec34bb40a.png)

你在很大程度上是一个相信自由意志的存在。然而，你真的不想再收到那些归因于你的谋杀事件。因此，你决定使用你的能力，试图让“至善主义”成为每个国家的主导宗教。

要让所有人都皈依“至善主义”，最少需要使用多少次你的能力？

有了神，一切皆有可能。但也许你不是神？如果不可能让“至善主义”成为所有国家的主导宗教，你也必须承认自己的凡人身份并如实说明。

## 说明/提示
在第一个测试用例中，可以通过两次使用能力来实现，如下所示：

第一次使用：

![图片](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1280B/5aa9a3e986e676e61c160aa9ee967c57ee4ce5c6.png)

第二次使用：

![图片](https://cdn.luogu.com.cn/upload/vjudge_pic/CF1280B/100b5a5b446d54b176a5d3a43e9d6e720401be64.png)

在第二个测试用例中，只需使用一次能力即可。

在第三个测试用例中，不可能让所有人都皈依“至善主义”，所以答案是“MORTAL”。

## 样例 #1
### 输入
```
4
7 8
AAPAAAAA
PPPPAAAA
PPPPAAAA
APAAPPPP
APAPPAPP
AAAAPPAP
AAAAPPAA
6 5
AAAAA
AAAAA
AAPAA
AAPAP
AAAPP
AAAPP
4 4
PPPP
PPPP
PPPP
PPPP
3 4
PPPP
PAAP
PPPP
```

### 输出
```
2
1
MORTAL
4
```

### 算法分类
无算法分类

### 综合分析与结论
这些题解的核心思路都是对矩阵中 `A` 的分布情况进行分类讨论，从而确定将矩阵中所有元素都变为 `A` 所需的最少操作次数。不同题解在具体实现细节和代码风格上有所差异，但整体逻辑相似。

### 所选题解
- **作者：_6_awa (赞：5)，4星**
    - **关键亮点**：思路清晰，代码简洁，对各种情况的判断逻辑明确，通过简单的遍历和条件判断就能得出结果。
- **作者：weizhiyonghu (赞：4)，4星**
    - **关键亮点**：先对时间复杂度进行分析，确保算法的可行性，然后详细分类讨论每种情况，代码结构清晰，函数封装合理。
- **作者：xieyikai2333 (赞：1)，4星**
    - **关键亮点**：重点在于代码实现的短小精悍，通过巧妙的逻辑判断和数组使用，用较少的代码实现了功能。

### 重点代码
#### 作者：_6_awa
```cpp
#include <iostream>
using namespace std;
int t,n,m;
char a[423][311];
int main()
{
    cin >> t;
    while(t --)
    {
        cin >> n >> m;
        int sum = 0,f = 4,b = 0,b2 = 0,b3 = 0,b4 = 0,sum2 = 0;
        for(int i = 1;i <= n;i ++)
            for(int j = 1;j <= m;j ++)
            {
                cin >> a[i][j];
                if(a[i][j] == 'A')sum ++;
                else sum2 ++;
                if(((i == 1 && j == 1) || (i == 1 && j == m) || (i == n && j == 1) || (i == n && j == m)) && a[i][j] == 'A')f = 2;
                if((i == 1 || j == 1 || i == n || j == m) && a[i][j] == 'A')f = min(f,3);
                if(i == 1 && a[i][j] == 'A')b ++;
                if(i == n && a[i][j] == 'A')b2 ++;
                if(j == 1 && a[i][j] == 'A')b3 ++;
                if(j == m && a[i][j] == 'A')b4 ++;
            }
        for(int i = 1;i <= n;i ++)
        {
            int num = 0;
            for(int j = 1;j <= m;j ++)
                if(a[i][j] == 'A')num ++;
            if(num == m)f = 2;
        }
        for(int j = 1;j <= m;j ++)
        {
            int num = 0;
            for(int i = 1;i <= n;i ++)
                if(a[i][j] == 'A')num ++;
            if(num == n)f = 2;
        }
        if(b == m || b2 == m || b3 == n || b4 == n)f = 1;
        if(sum == 0)cout << "MORTAL\n";
        else if(sum2 == 0)cout << "0\n";
        else cout << f << endl;
    }
}
```
**核心实现思想**：通过遍历矩阵，统计 `A` 和 `P` 的数量，同时记录矩阵四个角、四条边以及中间行和列中 `A` 的分布情况，根据这些信息判断属于哪种情况，从而确定最少操作次数。

#### 作者：weizhiyonghu
```cpp
inline bool check_line()
{
    bool flg1,flg2,flg3,flg4;
    flg1=flg2=flg3=flg4 = true;
    for(ri i = 1;i <= m;i++)
        flg1 = flg1 & (mp[1][i] == 'A'),
        flg2 = flg2 & (mp[n][i] == 'A');
    for(ri j = 1;j <= n;j++)
        flg3 = flg3 & (mp[j][1] == 'A'),
        flg4 = flg4 & (mp[j][m] == 'A');
    if(flg1||flg2||flg3||flg4) return true;
    else return false;
}

inline bool check_r()
{
    for(ri i = 1;i <= n;i++)
    {
        bool flg = true;
        for(ri j = 1;j <= m;j++)
            if(mp[i][j] == 'P')
                {flg=false;break;}
        if(flg == true) return true; 
    }
    return false;
}

inline bool check_c()
{
    for(ri i = 1;i <= m;i++)
    {
        bool flg = true;
        for(ri j = 1;j <= n;j++)
            if(mp[j][i] == 'P')
            {flg = false;break;}
        if(flg == true) return true;
    }
    return false;
}

int main()
{
    sp1,sp2;cin >> T;
    while(T --)
    {
        cin >> n >> m;bool is_all = true,is_none = true;
        for(ri i = 1;i <= n;i++)
            for(ri j = 1;j <= m;j++)
                cin >> mp[i][j],
                is_all &= (mp[i][j] == 'A'),
                is_none &= (mp[i][j] == 'P');
        if(is_none == true) {printf("MORTAL\n");continue;} 
        if(is_all == true) {printf("0\n");continue;}
        bool flg = check_line();
        if(flg == true){printf("1\n");continue;}
        bool is_r=check_r(),is_c=check_c();
        if(is_r||is_c) {printf("2\n");continue;}
        int ans = 0x3f3f3f3f;
        for(ri i = 1;i <= n;i++)
            for(ri j = 1;j <= m;j++)
                if(mp[i][j] == 'A')
                    if(i == 1 && j == 1) ans = min(ans,2);
                    else if(i == 1 && j == m) ans = min(ans,2);
                    else if(i == n && j == 1) ans = min(ans,2);
                    else if(i == n && j == m) ans = min(ans,2);
                    else if(i == n || j == m) ans = min(ans,3);
                    else if(i == 1 || j == 1) ans = min(ans,3);
        if(ans == 0x3f3f3f3f) ans = 4;
        printf("%d\n",ans);
    }
    fclose(stdin);
    return 0;
}
```
**核心实现思想**：将不同情况的判断封装成函数，提高代码的可读性和可维护性。先判断矩阵是否全为 `A` 或全为 `P`，然后依次判断是否有边全为 `A`、是否有行或列全为 `A`、四个角是否有 `A`、四条边是否有 `A` 等情况，根据判断结果确定最少操作次数。

#### 作者：xieyikai2333
```cpp
bool f[65];
void solve(){　
    memset(f,true,sizeof(f));
    int n,m,ans=INF;
    scanf("%d %d",&n,&m);
    for(int i=1;i<=n;i++){　
        bool flag=true;
        for(int j=1;j<=m;j++){　
            char ch;
            scanf(" %c",&ch);
            if(ch!='A')f[j]=flag=false;
            else ans=min(ans,4-(i==1||i==n)-(j==1||j==m));
        }
        if(flag)ans=min(ans,2-(i==1||i==n));
    }
    int cnt=0;
    for(int j=1;j<=m;j++)if(f[j])ans=min(ans,2-(j==1||j==m)),cnt++;
    if(cnt==m)puts("0");
    else if(ans==INF)puts("MORTAL");
    else printf("%d\n",ans);
    return;
}
```
**核心实现思想**：使用数组 `f` 记录每列是否全为 `A`，在遍历矩阵的过程中，根据当前元素的位置和值更新最少操作次数 `ans`。最后根据 `ans` 的值和 `f` 数组的情况输出结果。

### 最优关键思路或技巧
- **分类讨论**：将矩阵中 `A` 的分布情况分为全 `A`、全 `P`、有边全 `A`、有行或列全 `A`、角上有 `A`、边上有 `A`、内部有 `A` 等情况，分别处理，逻辑清晰。
- **标记数组**：使用标记数组记录矩阵的某些特征，如某行或某列是否全为 `A`，方便后续判断。
- **取最小值**：对于多种情况都满足的情况，取操作次数的最小值，确保结果是最少操作次数。

### 可拓展之处
同类型题可能会改变矩阵的操作规则，或者增加更多的元素类型和操作方式，但解题的核心思路仍然是对不同情况进行分类讨论。类似算法套路可以应用于其他需要根据不同条件进行分类处理的问题。

### 推荐题目
- [P1003 铺地毯](https://www.luogu.com.cn/problem/P1003)
- [P1047 校门外的树](https://www.luogu.com.cn/problem/P1047)
- [P1094 纪念品分组](https://www.luogu.com.cn/problem/P1094)

### 个人心得
- **作者：万弘**：第一次写的代码很丑然后就 WA 了，第二次改得好看了一点，核心内容似乎没变但就过了。这说明代码的可读性和规范性可能会影响调试和最终结果，良好的代码风格有助于减少错误。 

---
处理用时：99.35秒