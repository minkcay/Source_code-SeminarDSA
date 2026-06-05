#include <iostream>
#include <vector>
#include <string>

using namespace std;

static vector<string> s;
static vector<int> a;
static vector<int> tmp;
static vector<int> lenArr;
static int n;

static inline bool cmp(int a, int b)
{
    int la = lenArr[a];
    int lb = lenArr[b];

    return (la < lb) || (la == lb && s[a] < s[b]);
}

static inline void insertion_sort(int low, int high)
{
    for (int i = low + 1; i <= high; i++)
    {
        int key = a[i];
        int j = i - 1;

        while (j >= low && cmp(key, a[j]))
        {
            a[j + 1] = a[j];
            j--;
        }

        a[j + 1] = key;
    }
}

static void mergeSort(int left, int right)
{
    if (right - left <= 32)
    {
        insertion_sort(left, right);
        return;
    }

    int mid = left + ((right - left) >> 1);

    mergeSort(left, mid);
    mergeSort(mid + 1, right);

    if (!cmp(a[mid + 1], a[mid]))
        return;

    int i = left;
    int j = mid + 1;
    int k = left;

    while (i <= mid && j <= right)
    {
        if (cmp(a[i], a[j]))
            tmp[k++] = a[i++];
        else
            tmp[k++] = a[j++];
    }

    while (i <= mid)
        tmp[k++] = a[i++];

    while (j <= right)
        tmp[k++] = a[j++];

    for (int h = left; h <= right; h++)
        a[h] = tmp[h];
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;

    s.resize(n);
    a.resize(n);
    tmp.resize(n);
    lenArr.resize(n);

    size_t totalLen = 0;

    for (int i = 0; i < n; i++)
    {
        cin >> s[i];
        lenArr[i] = s[i].size();
        totalLen += lenArr[i] + 1;
        a[i] = i;
    }

    mergeSort(0, n - 1);

    string out;
    out.reserve(totalLen + 10);

    out += to_string(n);
    out += '\n';

    for (int i = 0; i < n; i++)
    {
        out += s[a[i]];
        out += '\n';
    }

    cout << out;

    return 0;
}
