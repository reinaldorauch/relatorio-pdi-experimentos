#include <iostream>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;
using namespace std;

int main(int argc, char const *argv[])
{
    if (argc != 2) {
        cout << "Uso: segmentacao [IMAGEM]" << endl;
    }

    Mat image = imread(argv[1], 1), imageSliced;

    if (!image.data) {
        cout << "Erro: Não foi possível abrir a imagem" << endl;
        return 1;
    }

    namedWindow("janela_origem", 1);
    imshow("janela_origem", image);

    threshold(image, imageSliced, 60, 255, 0);

    namedWindow("janela_threshold", 1);
    imshow("janela_threshold", imageSliced);

    inRange(imageSliced, Scalar(125, 0, 0), Scalar(255, 255, 255), imageSliced);

    namedWindow("janela_sliced1", 1);
    imshow("janela_sliced1", imageSliced);

    inRange(imageSliced, Scalar(155, 0, 0), Scalar(254, 255, 255), imageSliced);

    namedWindow("janela_sliced", 1);
    imshow("janela_sliced", imageSliced);

    waitKey(0);

    return 0;
}