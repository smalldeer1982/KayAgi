# 题目信息

# [ABC323F] Push and Carry

## 题目描述

[problemUrl]: https://atcoder.jp/contests/abc323/tasks/abc323_f

座標平面上に高橋君と荷物があります。

高橋君は現在 $ (X_A,Y_A) $ におり、荷物は $ (X_B,Y_B) $ にあります。 高橋君は荷物を $ (X_C,Y_C) $ まで運びたいです。

高橋君は $ (x,y) $ にいるとき、$ 1 $ 回の行動で次のいずれかの動きをすることができます。

- $ (x+1,y) $ に移動する。移動前の時点で荷物が $ (x+1,y) $ にあった時、荷物を $ (x+2,y) $ に移動させる。
- $ (x-1,y) $ に移動する。移動前の時点で荷物が $ (x-1,y) $ にあった時、荷物を $ (x-2,y) $ に移動させる。
- $ (x,y+1) $ に移動する。移動前の時点で荷物が $ (x,y+1) $ にあった時、荷物を $ (x,y+2) $ に移動させる。
- $ (x,y-1) $ に移動する。移動前の時点で荷物が $ (x,y-1) $ にあった時、荷物を $ (x,y-2) $ に移動させる。

荷物を $ (X_C,Y_C) $ に移動させるまでに必要な最小の行動回数を求めてください。

## 说明/提示

### 制約

- $ -10^{17}\leq\ X_A,Y_A,X_B,Y_B,X_C,Y_C\leq\ 10^{17} $
- $ (X_A,Y_A)\neq\ (X_B,Y_B) $
- $ (X_B,Y_B)\neq\ (X_C,Y_C) $
- 入力はすべて整数

### Sample Explanation 1

高橋君は次のように行動することで $ 9 $ 回で荷物を $ (0,5) $ に運ぶことができます。 - $ (2,2) $ へ移動する。 - $ (3,2) $ へ移動する。 - $ (3,3) $ へ移動する。荷物は $ (3,4) $ に移動する。 - $ (3,4) $ へ移動する。荷物は $ (3,5) $ に移動する。 - $ (4,4) $ へ移動する。 - $ (4,5) $ へ移動する。 - $ (3,5) $ へ移動する。荷物は $ (2,5) $ に移動する。 - $ (2,5) $ へ移動する。荷物は $ (1,5) $ に移動する。 - $ (1,5) $ へ移動する。荷物は $ (0,5) $ に移動する。 $ 8 $ 回以下で荷物を $ (0,5) $ に運ぶことができないので、$ 9 $ を出力します。

## 样例 #1

### 输入

```
1 2 3 3 0 5```

### 输出

```
9```

## 样例 #2

### 输入

```
0 0 1 0 -1 0```

### 输出

```
6```

## 样例 #3

### 输入

```
-100000000000000000 -100000000000000000 100000000000000000 100000000000000000 -100000000000000000 -100000000000000000```

### 输出

```
800000000000000003```

# AI分析结果

### 题目内容中文重写
在坐标平面上有高桥君和货物。

高桥君现在位于\((X_A,Y_A)\)，货物位于\((X_B,Y_B)\)。高桥君想把货物运到\((X_C,Y_C)\)。

高桥君在\((x,y)\)时，1次行动可以进行以下任意一种移动：
- 移动到\((x + 1,y)\)。若移动前货物在\((x + 1,y)\)，则将货物移动到\((x + 2,y)\)。
- 移动到\((x - 1,y)\)。若移动前货物在\((x - 1,y)\)，则将货物移动到\((x - 2,y)\)。
- 移动到\((x,y + 1)\)。若移动前货物在\((x,y + 1)\)，则将货物移动到\((x,y + 2)\)。
- 移动到\((x,y - 1)\)。若移动前货物在\((x,y - 1)\)，则将货物移动到\((x,y - 2)\)。

请求出将货物移动到\((X_C,Y_C)\)所需的最小行动次数。

### 综合分析与结论
这些题解的核心思路都是围绕着如何让人走到合适的位置推动箱子，然后将箱子移动到目标位置，通过分类讨论不同的位置关系来计算最小步数。
- **思路对比**：大部分题解都采用分类讨论的方法，根据箱子和目标点的位置关系（如在同一坐标轴、不同坐标轴等）进行分析。部分题解通过建立以箱子为原点的坐标系简化问题，还有题解直接考虑人走到箱子两侧的情况。
- **算法要点**：普遍用到曼哈顿距离公式计算两点间距离，对于人走到箱子旁边的路径被箱子阻挡的情况，会额外加2步。
- **解决难点**：主要难点在于处理人走到箱子旁边的路径被箱子阻挡的情况，以及箱子和目标点不在同一坐标轴时的转向问题。

### 所选题解
- **robertuu（4星）**
    - **关键亮点**：思路清晰，分类简单，只分横、纵、横纵都有三种情况。代码实现简洁，通过自定义距离函数处理路径被阻挡的情况。
    - **核心代码**：
```cpp
long long dist(long long xa,long long ya,long long xb,long long yb,long long xc,long long yc)
{
    long long res = abs(xa-xb)+abs(ya-yb);
    if(xa == xb && xb == xc && (ya < yc && yb > yc || ya > yc && yb < yc)) res += 2;
    if(ya == yb && yb == yc && (xa < xc && xb > xc || xa > xc && xb < xc)) res += 2;
    return res;
}
int main()
{
    long long xa,ya,xb,yb,xc,yc;
    cin >> xa >> ya >> xb >> yb >> xc >> yc;
    int X = 0,Y = 0;
    if(xc > xb) X = -1;
    if(xc < xb) X = 1;
    if(yc > yb) Y = -1;
    if(yc < yb) Y = 1;
    if(X == 0) cout << dist(xa,ya,xb,yb+Y,xb,yb)+abs(yb-yc);
    else if(Y == 0) cout << dist(xa,ya,xb+X,yb,xb,yb)+abs(xb-xc);
    else cout << min(dist(xa,ya,xb,yb+Y,xb,yb),dist(xa,ya,xb+X,yb,xb,yb))+abs(yb-yc)+abs(xb-xc)+2;
    return 0;
}
```
- **not_clever_syl（4星）**
    - **关键亮点**：思路简洁明了，先判断货物和目的地是否在同一坐标轴，再分别计算答案。代码逻辑清晰，通过自定义距离函数处理路径被阻挡的情况。
    - **核心代码**：
```cpp
long long dis(long long x,long long y,long long tx,long long ty){
    return abs(x-tx)+abs(y-ty);
}
long long gdis(long long x,long long y,long long tx,long long ty,long long xb,long long yb){
    bool fl=false;
    if(x==tx&&xb==x&&min(y,ty)<=yb&&yb<=max(y,ty))fl=true;
    if(y==ty&&yb==y&&min(x,tx)<=xb&&xb<=max(x,tx))fl=true;
    return abs(x-tx)+abs(y-ty)+(fl?2:0);
}
signed main(){
    ios::sync_with_stdio(0),cin.tie(0),cout.tie(0);
    long long xa,ya,xb,yb,xc,yc;
    cin>>xa>>ya>>xb>>yb>>xc>>yc;
    if(xb==xc){
        auto ryb=yb;
        if(yb<yc)--yb;
        else ++yb;
        auto ans=gdis(xa,ya,xb,yb,xb,ryb)+dis(xb,yb,xc,yc)-1;
        cout<<ans;
        return 0;
    }
    if(yb==yc){
        auto rxb=xb;
        if(xb<xc)--xb;
        else ++xb;
        auto ans=gdis(xa,ya,xb,yb,rxb,yb)+dis(xb,yb,xc,yc)-1;
        cout<<ans;
        return 0;
    }
    long long ans1,ans2;
    if(xb<xc)ans1=gdis(xa,ya,xb-1,yb,xb,yb);
    else     ans1=gdis(xa,ya,xb+1,yb,xb,yb);
    if(yb<yc)ans2=gdis(xa,ya,xb,yb-1,xb,yb);
    else     ans2=gdis(xa,ya,xb,yb+1,xb,yb);
    auto t=dis(xb,yb,xc,yc)+2;
    cout<<min(ans1,ans2)+t;
}
```
- **incra（4星）**
    - **关键亮点**：思路清晰，通过自定义距离函数处理路径被阻挡的情况，代码实现简洁。
    - **核心代码**：
```cpp
bool check (PLL x,PLL a,PLL b) {
    if (x == a || x == b) return false;
    if (min (a.x,b.x) <= x.x && x.x <= max (a.x,b.x) && min (a.y,b.y) <= x.y && x.y <= max (a.y,b.y)) return true;
    return false;
}
LL get_dis (PLL a,PLL b,PLL c = {-1e17,-1e17}) {
    if (a.x == b.x && a.x == c.x && min (a.y,b.y) <= c.y && c.y <= max (a.y,b.y)) return abs (a.x - b.x) + abs (a.y - b.y) + 2;
    if (a.y == b.y && a.y == c.y && min (a.x,b.x) <= c.x && c.x <= max (a.x,b.x)) return abs (a.x - b.x) + abs (a.y - b.y) + 2;
    return abs (a.x - b.x) + abs (a.y - b.y);
}
int main () {
    cin >> a >> b >> c;
    int dx = b.x == c.x ? 0 : (b.x - c.x) / abs (b.x - c.x),dy = b.y == c.y ? 0 : (b.y - c.y) / abs (b.y - c.y);
    if (!dx) cout << get_dis (a,{b.x,b.y + dy},b) + abs (b.x - c.x) + abs (b.y - c.y) << endl;
    else if (!dy) cout << get_dis (a,{b.x + dx,b.y},b) + abs (b.x - c.x) + abs (b.y - c.y) << endl;
    else cout << min (get_dis (a,{b.x + dx,b.y},b) + (dy ? 2 : 0),
        get_dis (a,{b.x,b.y + dy},b) + (dx ? 2 : 0)) + abs (b.x - c.x) + abs (b.y - c.y) << endl;
    return 0;
}
```

### 最优关键思路或技巧
- **分类讨论**：根据箱子和目标点的位置关系进行分类讨论，简化问题。
- **自定义距离函数**：处理人走到箱子旁边的路径被箱子阻挡的情况，统一计算距离。

### 可拓展之处
同类型题如更复杂的推箱子问题，可能会有障碍物、多个箱子等情况。类似算法套路还是通过分类讨论不同情况，结合距离计算和路径判断来求解。

### 推荐题目
- [P1162 填涂颜色](https://www.luogu.com.cn/problem/P1162)
- [P1036 选数](https://www.luogu.com.cn/problem/P1036)
- [P1012 拼数](https://www.luogu.com.cn/problem/P1012)

### 个人心得摘录与总结
- **无钩七不改名**：赛时采用建立以箱子为原点的坐标系，通过坐标变换分类讨论的方法，但未给出代码。总结是该方法虽然繁琐，但能覆盖所有情况。
- **WhileTrueRP**：在三点呈 L 形状的情况卡了十分钟，说明这种特殊情况需要仔细分析。总结是分类讨论时要全面考虑各种情况，注意特殊情况的处理。

---
处理用时：55.89秒