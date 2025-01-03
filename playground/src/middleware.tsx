// middleware.js
import { NextRequest, NextResponse } from 'next/server';

const AGENT_SERVER_URL = process.env.AGENT_SERVER_URL || 'http://localhost:8080';
const NYRA_DEV_SERVER_URL = process.env.NYRA_DEV_SERVER_URL || 'http://localhost:49483';

console.log('Middleware initialized with:', {
    AGENT_SERVER_URL,
    NYRA_DEV_SERVER_URL
});

export async function middleware(req: NextRequest) {
    const { pathname } = req.nextUrl;
    const url = req.nextUrl.clone();

    console.log(`Processing request for path: ${pathname}`);

    if (pathname.startsWith(`/api/agents/`)) {
        url.href = `${AGENT_SERVER_URL}${pathname.replace('/api/agents/', '/')}`;
        console.log(`Rewriting agents request to: ${url.href}`);
        return NextResponse.rewrite(url);
    } else if (pathname.startsWith(`/api/vector/`)) {
        url.href = `${AGENT_SERVER_URL}${pathname.replace('/api/vector/', '/vector/')}`;
        console.log(`Rewriting vector request to: ${url.href}`);
        return NextResponse.rewrite(url);
    } else if (pathname.startsWith(`/api/token/`)) {
        url.href = `${AGENT_SERVER_URL}${pathname.replace('/api/token/', '/token/')}`;
        console.log(`Rewriting token request to: ${url.href}`);
        return NextResponse.rewrite(url);
    } else if (pathname.startsWith('/api/dev/')) {
        const playgroundPath = pathname.replace('/api/dev/', '/api/playground/');
        url.href = `${NYRA_DEV_SERVER_URL}${playgroundPath}`;
        console.log(`Rewriting playground request to: ${url.href}`);
        return NextResponse.rewrite(url);
    }

    return NextResponse.next();
}