# 题目信息

# Just Arrange the Icons

## 题目描述

BerPhone X is almost ready for release with $ n $ applications being preinstalled on the phone. A category of an application characterizes a genre or a theme of this application (like "game", "business", or "education"). The categories are given as integers between $ 1 $ and $ n $ , inclusive; the $ i $ -th application has category $ c_i $ .

You can choose $ m $ — the number of screens and $ s $ — the size of each screen. You need to fit all $ n $ icons of the applications (one icon representing one application) meeting the following requirements:

- On each screen, all the icons must belong to applications of the same category (but different screens can contain icons of applications of the same category);
- Each screen must be either completely filled with icons (the number of icons on the screen is equal to $ s $ ) or almost filled with icons (the number of icons is equal to $ s-1 $ ).

Your task is to find the minimal possible number of screens $ m $ .

## 说明/提示

In the first test case of the example, all the icons can be placed on three screens of size $ 4 $ : a screen with $ 4 $ icons of the category $ 1 $ , a screen with $ 3 $ icons of the category $ 1 $ , and a screen with $ 4 $ icons of the category $ 5 $ .

## 样例 #1

### 输入

```
3
11
1 5 1 5 1 5 1 1 1 1 5
6
1 2 2 2 2 1
5
4 3 3 1 2
```

### 输出

```
3
3
4
```

# AI分析结果

### 题目翻译
# 排列图标

## 题目描述
BerPhone X 几乎准备好发布了，手机上预装了 $ n $ 个应用程序。应用程序的类别表征了该应用程序的类型或主题（如“游戏”、“商务”或“教育”）。类别用 $ 1 $ 到 $ n $ 之间（包含 $ 1 $ 和 $ n $）的整数表示；第 $ i $ 个应用程序的类别为 $ c_i $。

你可以选择 $ m $（屏幕数量）和 $ s $（每个屏幕的大小）。你需要将所有 $ n $ 个应用程序的图标（一个图标代表一个应用程序）进行排列，同时满足以下要求：
- 在每个屏幕上，所有图标必须属于同一类别的应用程序（但不同屏幕可以包含同一类别的应用程序图标）；
- 每个屏幕必须要么完全被图标填满（屏幕上的图标数量等于 $ s $），要么几乎被图标填满（图标数量等于 $ s - 1 $）。

你的任务是找到最小可能的屏幕数量 $ m $。

## 说明/提示
在示例的第一个测试用例中，所有图标可以放在三个大小为 $ 4 $ 的屏幕上：一个屏幕放 $ 4 $ 个类别为 $ 1 $ 的图标，一个屏幕放 $ 3 $ 个类别为 $ 1 $ 的图标，一个屏幕放 $ 4 $ 个类别为 $ 5 $ 的图标。

## 样例 #1
### 输入
```
3
11
1 5 1 5 1 5 1 1 1 1 5
6
1 2 2 2 2 1
5
4 3 3 1 2
```
### 输出
```
3
3
4
```

### 算法分类
枚举

### 综合分析与结论
- **思路对比**：三位作者的核心思路都是通过枚举屏幕容量，计算每个容量下所需的屏幕数，然后取最小值。yuzhechuan 和 gyh20 都明确提到了根据同种类软件数计算所需屏幕数的公式以及合法性判断，而 Refined_heart 则是通过不同的方式判断是否满足条件。
- **算法要点**：都利用了贪心思想，即尽量装满每个屏幕，剩余的额外开一个屏幕。同时，都通过枚举屏幕容量来找到最小的屏幕数。
- **解决难点**：关键在于如何判断给定的屏幕容量和屏幕数是否能满足所有应用程序图标的放置要求，三位作者都通过计算左边界来进行判断。

### 题解评分
- **yuzhechuan**：4星。思路清晰，对复杂度进行了详细的分析和证明，代码结构良好，注释明确。
- **gyh20**：4星。思路简洁明了，代码实现较为高效，对时间复杂度有合理的分析。
- **Refined_heart**：3星。思路有一定的创新性，但代码中存在一些不必要的变量和操作，复杂度分析不够详细。

### 所选题解
- **yuzhechuan（4星）**
  - **关键亮点**：思路清晰，对复杂度进行了详细的分析和证明，代码结构良好，注释明确。
- **gyh20（4星）**
  - **关键亮点**：思路简洁明了，代码实现较为高效，对时间复杂度有合理的分析。

### 重点代码
#### yuzhechuan 的核心代码
```cpp
int calc(int x){
    int res=0;
    for(int i=0;i<g.size();i++){
        int now=(g[i]-1)/x+1; //套用式子2
        if((x-1)*now<=g[i]) res+=now; //判定是否满足式子1（只判了左边界）
        else return INT_MAX; //不合法
    }
    return res;
}

void doit(){
    read(n);
    for(int i=1;i<=n;i++) cnt[i]=0; //清空桶
    for(int i=1,x;i<=n;i++) cnt[read(x)]++;
    g.clear();
    int mi=n;
    for(int i=1;i<=n;i++) if(cnt[i]) g.push_back(cnt[i]),mi=min(mi,cnt[i]); //记录下桶中的最少数量
    int ans=n;
    for(int i=mi+1;i>1;i--) ans=min(ans,calc(i)); //枚举单页容量，分别计算出所需面数，取个最小值
    write(ans);puts("");
}
```
**核心实现思想**：`calc` 函数用于计算给定屏幕容量下所需的屏幕数，并判断是否合法。`doit` 函数负责读取输入，统计每种应用程序的数量，然后枚举屏幕容量，调用 `calc` 函数计算所需屏幕数，取最小值作为最终结果。

#### gyh20 的核心代码
```cpp
while(1){
    ans=0;
    ia=0;
    for(re int i=1;i<=cnt;++i){
        int tmp=(p[i]-1)/mn+1;
        ans+=tmp;
        if((mn-1)*tmp>p[i]){ia=1;break;
        }
    }
    if(!ia)break;
    --mn;
}
```
**核心实现思想**：通过不断减小屏幕容量，计算所需屏幕数，并判断是否合法，直到找到合法的最小屏幕容量。

### 最优关键思路或技巧
- 利用贪心思想，尽量装满每个屏幕，剩余的额外开一个屏幕。
- 枚举屏幕容量，通过计算左边界来判断是否合法，从而找到最小的屏幕数。
- 利用桶排序统计每种应用程序的数量，提高效率。

### 可拓展之处
同类型题可以是类似的资源分配问题，要求在满足一定条件下找到最优的分配方案。类似算法套路可以是枚举和贪心结合，通过枚举不同的参数，利用贪心思想计算结果，然后取最优解。

### 推荐洛谷题目
- P1007 独木桥
- P1223 排队接水
- P1803 凌乱的yyy / 线段覆盖

---
处理用时：41.80秒