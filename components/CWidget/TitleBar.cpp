#include "TitleBar.h"
#include <QHBoxLayout>
#include <QPainter>
#include <QFile>
#include <QMouseEvent>
#include <QIcon>

#define TITLE_HEIGHT 30         // 标题栏高度;

TitleBar::TitleBar(QWidget *parent)
	: QWidget(parent)
	//, ui(new Ui::TitleBar)
	, m_colorR(153)
	, m_colorG(153)
	, m_colorB(153)
	, m_isPressed(false)
	, m_buttonType(MIN_MAX_BUTTON)
	, m_windowBorderWidth(2)
	, m_isTransparent(false)
{
	//ui->setupUi(this);
	// 初始化;
	initControl();
	initConnections();
}

TitleBar::~TitleBar()
{
	//delete ui;
}

// 初始化控件;
void TitleBar::initControl()
{
	m_pIcon = new QLabel;
	m_pTitleContent = new QLabel;

	m_pButtonMin = new QPushButton;
	m_pButtonRestore = new QPushButton;
	m_pButtonMax = new QPushButton;
	m_pButtonClose = new QPushButton;

	m_pButtonMin->setFixedSize(QSize(TITLE_HEIGHT, TITLE_HEIGHT));
	m_pButtonRestore->setFixedSize(QSize(TITLE_HEIGHT, TITLE_HEIGHT));
	m_pButtonMax->setFixedSize(QSize(TITLE_HEIGHT, TITLE_HEIGHT));
	m_pButtonClose->setFixedSize(QSize(TITLE_HEIGHT, TITLE_HEIGHT));

	m_pTitleContent->setObjectName("TitleContent");
	m_pButtonMin->setObjectName("ButtonMin");
	m_pButtonRestore->setObjectName("ButtonRestore");
	m_pButtonMax->setObjectName("ButtonMax");
	m_pButtonClose->setObjectName("ButtonClose");

	m_pButtonMin->setIcon(QIcon(":/icons/assets/baseline_minimize_black_18dp.png"));
	m_pButtonRestore->setIcon(QIcon(":/icons/assets/icons8-restore-down-32.png"));
	m_pButtonMax->setIcon(QIcon(":/icons/assets/icons8-maximize-button-26.png"));
	m_pButtonClose->setIcon(QIcon(":/icons/assets/baseline_close_black_18dp.png"));

	m_pButtonMin->setToolTip(QStringLiteral("最小化"));
	m_pButtonRestore->setToolTip(QStringLiteral("还原"));
	m_pButtonMax->setToolTip(QStringLiteral("最大化"));
	m_pButtonClose->setToolTip(QStringLiteral("关闭"));
	m_pButtonRestore->hide();

	QHBoxLayout* mylayout = new QHBoxLayout(this);
	mylayout->addWidget(m_pIcon);
	mylayout->addWidget(m_pTitleContent);

	mylayout->addWidget(m_pButtonMin);
	mylayout->addWidget(m_pButtonRestore);
	mylayout->addWidget(m_pButtonMax);
	mylayout->addWidget(m_pButtonClose);

	mylayout->setContentsMargins(5, 0, 0, 0);
	mylayout->setSpacing(0);

	m_pTitleContent->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

	this->setFixedHeight(TITLE_HEIGHT);
	this->setWindowFlags(Qt::FramelessWindowHint);
	this->setStyleSheet("background:red");
}

// 信号槽的绑定;
void TitleBar::initConnections()
{
	connect(m_pButtonMin, SIGNAL(clicked()), this, SLOT(onButtonMinClicked()));
	connect(m_pButtonRestore, SIGNAL(clicked()), this, SLOT(onButtonRestoreClicked()));
	connect(m_pButtonMax, SIGNAL(clicked()), this, SLOT(onButtonMaxClicked()));
	connect(m_pButtonClose, SIGNAL(clicked()), this, SLOT(onButtonCloseClicked()));
}

// 设置标题栏背景色,在paintEvent事件中进行绘制标题栏背景色;
// 在构造函数中给了默认值，可以外部设置颜色值改变标题栏背景色;
void TitleBar::setBackgroundColor(int r, int g, int b, bool isTransparent)
{
	m_colorR = r;
	m_colorG = g;
	m_colorB = b;
	m_isTransparent = isTransparent;
	// 重新绘制（调用paintEvent事件）;
	update();
}

// 设置标题栏图标;
void TitleBar::setTitleIcon(QString filePath, QSize IconSize)
{
	QPixmap titleIcon(filePath);
	m_pIcon->setPixmap(titleIcon.scaled(IconSize));
}

// 设置标题内容;
void TitleBar::setTitleContent(QString titleContent, int titleFontSize)
{
	// 设置标题字体大小;
	QFont font = m_pTitleContent->font();
	font.setPointSize(titleFontSize);
	m_pTitleContent->setFont(font);
	// 设置标题内容;
	m_pTitleContent->setText(titleContent);
	m_titleContent = titleContent;
}


// 设置标题栏上按钮类型;
// 由于不同窗口标题栏上的按钮都不一样，所以可以自定义标题栏中的按钮;
// 这里提供了四个按钮，分别为最小化、还原、最大化、关闭按钮，如果需要其他按钮可自行添加设置;
void TitleBar::setButtonType(ButtonType buttonType)
{
	m_buttonType = buttonType;

	switch (buttonType)
	{
	case MIN_BUTTON:
	{
		m_pButtonRestore->setVisible(false);
		m_pButtonMax->setVisible(false);
	}
	break;
	case MIN_MAX_BUTTON:
	{
		m_pButtonRestore->setVisible(false);
	}
	break;
	case ONLY_CLOSE_BUTTON:
	{
		m_pButtonMin->setVisible(false);
		m_pButtonRestore->setVisible(false);
		m_pButtonMax->setVisible(false);
	}
	break;
	default:
		break;
	}
}

// 设置窗口边框宽度;
void TitleBar::setWindowBorderWidth(int borderWidth)
{
	m_windowBorderWidth = borderWidth;
}


// 绘制标题栏背景色;
void TitleBar::paintEvent(QPaintEvent *event)
{
	//// 是否设置标题透明;
	//if (!m_isTransparent)
	//{
	//	//设置背景色;
	//	QPainter painter(this);
	//	QPainterPath pathBack;
	//	pathBack.setFillRule(Qt::WindingFill);
	//	pathBack.addRoundedRect(QRect(0, 0, this->width(), this->height()), 0, 0);
	//	painter.setRenderHint(QPainter::Antialiasing, true);
	//	painter.fillPath(pathBack, QBrush(QColor(m_colorR, m_colorG, m_colorB)));
	//}

	//// 当窗口最大化或者还原后，窗口长度变了，标题栏的长度应当一起改变;
	//// 这里减去m_windowBorderWidth ，是因为窗口可能设置了不同宽度的边框;
	//// 如果窗口有边框则需要设置m_windowBorderWidth的值，否则m_windowBorderWidth默认为0;
	//if (this->width() != (this->parentWidget()->width() - m_windowBorderWidth))
	//{
	//	this->setFixedWidth(this->parentWidget()->width() - m_windowBorderWidth);
	//}
	QWidget::paintEvent(event);
}

// 双击响应事件，主要是实现双击标题栏进行最大化和最小化操作;
void TitleBar::mouseDoubleClickEvent(QMouseEvent *event)
{
	// 只有存在最大化、还原按钮时双击才有效;
	if (m_buttonType == MIN_MAX_BUTTON)
	{
		// 通过最大化按钮的状态判断当前窗口是处于最大化还是原始大小状态;
		// 或者通过单独设置变量来表示当前窗口状态;
		if (m_pButtonMax->isVisible())
		{
			onButtonMaxClicked();
		}
		else
		{
			onButtonRestoreClicked();
		}
	}

	return QWidget::mouseDoubleClickEvent(event);
}

// 以下通过mousePressEvent、mouseMoveEvent、mouseReleaseEvent三个事件实现了鼠标拖动标题栏移动窗口的效果;
void TitleBar::mousePressEvent(QMouseEvent *event)
{
	if (m_buttonType == MIN_MAX_BUTTON)
	{
		// 在窗口最大化时禁止拖动窗口;
		if (m_pButtonMax->isVisible())
		{
			m_isPressed = true;
			m_startMovePos = event->globalPos();
		}
	}
	else
	{
		m_isPressed = true;
		m_startMovePos = event->globalPos();
	}

	return QWidget::mousePressEvent(event);
}

void TitleBar::mouseMoveEvent(QMouseEvent *event)
{
	if (m_isPressed)
	{
		QPoint movePoint = event->globalPos() - m_startMovePos;
		QPoint widgetPos = this->parentWidget()->pos();
		m_startMovePos = event->globalPos();
		this->parentWidget()->move(widgetPos.x() + movePoint.x(), widgetPos.y() + movePoint.y());
	}
	return QWidget::mouseMoveEvent(event);
}

void TitleBar::mouseReleaseEvent(QMouseEvent *event)
{
	m_isPressed = false;
	return QWidget::mouseReleaseEvent(event);
}

// 以下为按钮操作响应的槽;
void TitleBar::onButtonMinClicked()
{
	emit signalButtonMinClicked();
}

void TitleBar::onButtonRestoreClicked()
{
	m_pButtonRestore->setVisible(false);
	m_pButtonMax->setVisible(true);
	emit signalButtonRestoreClicked();
}

void TitleBar::onButtonMaxClicked()
{
	m_pButtonMax->setVisible(false);
	m_pButtonRestore->setVisible(true);
	emit signalButtonMaxClicked();
}

void TitleBar::onButtonCloseClicked()
{
	emit signalButtonCloseClicked();
}

