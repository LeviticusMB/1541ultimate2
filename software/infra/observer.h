/*
 * observer.h
 *
 *  Created on: Jul 11, 2015
 *      Author: Gideon
 */

#ifndef INFRA_OBSERVER_H_
#define INFRA_OBSERVER_H_

#include <stdio.h>
#include "FreeRTOS.h"
#include "queue.h"

class ObserverQueue {
	QueueHandle_t queue;
	int polls;
public:
	ObserverQueue() {
		queue = xQueueCreate(8, sizeof(void *));
		polls = 0;
	}
	virtual ~ObserverQueue() {
		vQueueDelete(queue);
	}
	void putEvent(void *el, int q) {
#ifdef OS
		if (!xQueueSend(queue, &el, 5)) {
			printf("Failed to post message to queue #%d (polled %d times).\n", q, polls);
		}
#endif
	}
	void *waitForEvent(uint32_t ticks) {
		polls++;
		void *result = 0;
		xQueueReceive(queue, &result, (TickType_t)ticks);
		return result;
	}
};

#endif /* INFRA_OBSERVER_H_ */
