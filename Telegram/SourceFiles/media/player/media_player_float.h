/*
This file is part of Telegram Desktop,
the official desktop version of Telegram messaging app, see https://telegram.org

Telegram Desktop is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

It is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

In addition, as a special exception, the copyright holders give permission
to link the code of portions of this program with the OpenSSL library.

Full license: https://github.com/telegramdesktop/tdesktop/blob/master/LICENSE
Copyright (c) 2014-2017 John Preston, https://desktop.telegram.org
*/
#pragma once

namespace Media {
namespace Clip {
class Playback;
} // namespace Clip

namespace Player {

class Float : public TWidget, private base::Subscriber {
public:
	Float(QWidget *parent, HistoryItem *item, base::lambda<void(bool visible)> toggleCallback);

	HistoryItem *item() const {
		return _item;
	}
	void setOpacity(float64 opacity) {
		_opacity = opacity;
		update();
	}
	void detach();
	bool detached() const {
		return !_item;
	}
	void ui_repaintHistoryItem(const HistoryItem *item) {
		if (item == _item) {
			repaintItem();
		}
	}

protected:
	void paintEvent(QPaintEvent *e);

private:
	Clip::Reader *getReader() const;
	void repaintItem();
	void prepareShadow();
	bool hasFrame() const;
	bool fillFrame();
	QRect getInnerRect() const;
	void updatePlayback();

	HistoryItem *_item = nullptr;
	base::lambda<void(bool visible)> _toggleCallback;

	float64 _opacity = 1.;

	QPixmap _shadow;
	QImage _frame;

	std::unique_ptr<Clip::Playback> _roundPlayback;

};

} // namespace Player
} // namespace Media