// pages/_app.tsx
import type { AppProps } from 'next/app';
import '../app/globals.css';
import { ApolloProvider } from '@apollo/client/react';
import { initializeApollo } from '../lib/apolloClient';

const apolloClient = initializeApollo();

function MyApp({ Component, pageProps }: AppProps) {
    return (
        <ApolloProvider client={apolloClient}>
            <Component {...pageProps} />
        </ApolloProvider>
    );
}

export default MyApp;
