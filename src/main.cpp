#include <QApplication>
#include <QLabel>
#include <QMainWindow>
#include <QTimer>
#include <QVBoxLayout>
#include <QWidget>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QCoreApplication::setApplicationName(QStringLiteral("UniversalWork"));
    QCoreApplication::setApplicationVersion(QStringLiteral("0.1.0"));
    QCoreApplication::setOrganizationName(QStringLiteral("UniversalWork"));

    QMainWindow window;
    window.setWindowTitle(QCoreApplication::applicationName());
    window.resize(960, 640);

    auto *content = new QWidget(&window);
    auto *layout = new QVBoxLayout(content);
    layout->setContentsMargins(48, 48, 48, 48);
    layout->addStretch();
    auto *title = new QLabel(QStringLiteral("UniversalWork"), content);
    auto font = title->font();
    font.setPointSize(28);
    font.setBold(true);
    title->setFont(font);
    title->setAlignment(Qt::AlignCenter);
    layout->addWidget(title);
    auto *subtitle = new QLabel(QStringLiteral("Your local-first AI workspace."), content);
    subtitle->setAlignment(Qt::AlignCenter);
    layout->addWidget(subtitle);
    layout->addStretch();
    window.setCentralWidget(content);
    window.show();

    if (QCoreApplication::arguments().contains(QStringLiteral("--smoke-test"))) {
        QTimer::singleShot(0, &app, [] { QCoreApplication::quit(); });
    }
    return app.exec();
}
