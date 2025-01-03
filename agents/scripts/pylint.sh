#!/bin/bash

pylint ./agents/nyra_packages/extension/. || pylint-exit --warn-fail --error-fail $?