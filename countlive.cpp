int countlive(const int x, const int y, int& hight, int& width, char** arr) {
    int nu[8][2];
    int n1, n2;
    checkpoint(nu, x, y, hight, width);
    int count = 0;

    for (int k = 0; k < 8; ++k) {
        n1 = nu[k][0];
        n2 = nu[k][1];
        if ((n1 >= 0) && (n1 < hight) && (n2 >= 0) && (n2 < width)) {
            if (arr[n1][n2] == '*') {
                ++count;
            }
        }
    }
    return count;
}
