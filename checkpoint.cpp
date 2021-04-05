void checkpoint(int nu[8][2], const int x, const int y, const int& hight, const int& width) {
    int k = 0;

    for (int i = x - 1; i <= x + 1; ++i) {

        for (int j = y - 1; j <= y + 1; ++j) {

            if ((i >= 0) && (i < hight) && (j >= 0) && (j < width)) {
                if ((i == x) && (j == y)) {
                    continue;
                }

                else {
                    nu[k][0] = i;
                    nu[k][1] = j;
                    k++;
                }
            }

            else {
                nu[k][0] = i;
                nu[k][1] = j;
                k++;
            }
        }
    }
}




