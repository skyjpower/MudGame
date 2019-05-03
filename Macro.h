#pragma once

#define SAFE_DELETE(p) if(p) { free(p); }